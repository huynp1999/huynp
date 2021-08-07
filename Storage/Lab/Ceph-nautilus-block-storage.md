# Block storage
Block storage được dùng để chứa máy ảo trong môi trường cloud hoặc có thể là disk được gắn thêm cho máy ảo hoặc máy chủ client thông thường, disk gắn thêm này được cấp ra từ cụm cluser CEPH.

![image](https://user-images.githubusercontent.com/83684068/128485927-980c308b-dc16-4d77-9c9c-e4005937507e.png)

Sử dụng mô hình từ phần trước thêm node client01 có public IP là `10.10.10.20`

![image](https://github.com/huynp1999/huynp/blob/master/pic/storage/nau/ceph9.PNG)

## Setup client01
Update thêm alias client01 trong file `/etc/hosts` của cả client và cluster

    192.168.62.84 client01
    192.168.62.85 ceph01
    192.168.62.86 ceph02
    192.168.62.87 ceph03

Cài đặt các gói hỗ trợ

    # apt install git python-setuptools python-virtualenv chrony -y
    
Tạo user `cephuser` và cấp quyền sudo

    # useradd -d /home/cephuser -m cephuser
    # passwd cephuser

    # echo "cephuser ALL = (root) NOPASSWD:ALL" | sudo tee /etc/sudoers.d/cephuser
    # chmod 0440 /etc/sudoers.d/cephuser
    
## Setup ceph-admin (ceph01)
Sau khi setup xong cho client, copy key-pair và cài đặt các gói Ceph Nautilus cho `client01`, thực hiện từ từ ceph-admin `ceph01`

    # su - cephuser
    $ cd my-cluster
    $ ssh-copy-id cephuser@client01
    
    $ ceph-deploy install --release nautilus client01

Deploy node client01 và phân quyền cho key admin

    $ ceph-deploy admin client01
    $ ssh cephuser@client01 'sudo chmod +r /etc/ceph/ceph.client.admin.keyring'
    
## Cấu hình RBD pool trên ceph-admin
Khai báo tên của pool block storage là `rbdpool1` để client sử dụng. Pool mặc định của Ceph là `rbd`.
    
    $ ceph osd pool create rbdpool1 128
    pool 'rbdpool1' created
    
    $ rbd pool init rbdpool1

Kiểm tra các pool

    $ ceph osd pool ls
    .rgw.root
    default.rgw.control
    default.rgw.meta
    default.rgw.log
    rbd
    rbdpool1

Như vậy đã tạo pool block storage thành công, tiếp theo chuyển sang client để tạo ra image (disk) từ pool này và mount để sử dụng

## Sử dụng pool trên client
Đứng trên node client01 thực hiện tạo một image có tên là disk02 với dung lượng là 6GB, image này sẽ nằm trong pool có tên là `rdbpool1` vừa tạo xong

    root@client01:~# rbd create disk02 --size 6G --image-feature layering -p rbdpool1
    
Liệt kê các image thuộc pool `rbdpool`, nếu ko có option `-p` Ceph sẽ liệt kê pool mặc định là `rbd`

    root@client01:~# rbd ls -l -p rbdpool1
    NAME   SIZE  PARENT FMT PROT LOCK
    disk02 6 GiB          2

Sau khi tạo thành công image, cần phải gắn nó vào máy ảo và format, sau đó tiếp tục mount vào thư mục cần thiết.

Thực hiện map images đã được tạo thành một device của máy client.
Lệnh map này sẽ thực hiện map image có tên là disk02 tới một thiết bị trên client, thiết bị này sẽ được đặt tên là `/dev/rdbX`. Trong đó X sẽ bắt đầu từ 0 và tăng dần với các image sau.

    root@client01:~# rbd map disk02 -p rbdpool1
    /dev/rbd1

Kiểm tra image RBD có tên là disk02 đã được map hay chưa.

    root@client01:~# rbd showmapped
    id pool     namespace image  snap device
    0  rbd                disk01 -    /dev/rbd0
    1  rbdpool1           disk02 -    /dev/rbd1

Format xfs cho device

    mkfs.xfs /dev/rbd1
    
 Và mount vào có thể sử dụng được
 
    mount /dev/rbd1 /opt
    
 Kiểm tra
 
    root@client01:~# lsblk
    NAME   MAJ:MIN RM  SIZE RO TYPE MOUNTPOINT
    sda      8:0    0   20G  0 disk
    ├─sda1   8:1    0    1M  0 part
    └─sda2   8:2    0   20G  0 part /
    sdb      8:16   0   20G  0 disk
    sdc      8:32   0   20G  0 disk
    sr0     11:0    1  945M  0 rom
    rbd0   252:0    0    5G  0 disk /mnt
    rbd1   252:16   0    6G  0 disk /opt

Kiểm tra trên dashboard

![image](https://github.com/huynp1999/huynp/blob/master/pic/storage/nau/ceph8.PNG)

Lưu ý: mountpoint của device RBD sẽ bị mất khi khởi động lại hệ thống, nên cần khai báo trong `/etc/fstab` với nội dung sau

    /dev/rbd/rbdpool1/disk02             /opt                    xfs     noauto          0 0

Rbdmap cũng bị mất sau khi reboot, cập nhật file `vim /etc/ceph/rbdmap` bằng việc thêm dòng `rbd/disk02 id=admin,keyring=/etc/ceph/ceph.client.admin.keyring` vào cuối file

    [root@client1 ~]# cat /etc/ceph/rbdmap
    # RbdDevice             Parameters
    #poolname/imagename     id=client,keyring=/etc/ceph/ceph.client.keyring
    rbd/disk02    id=admin,keyring=/etc/ceph/ceph.client.admin.keyring

Trong đó:
- rbd/disk02: dược khai báo theo cú pháp pool_name/image_name
- id: là giá trị admin
- keyring: là đường dẫn file key được tạo ở bước trước đó.

# Benchmark image RBD đã được mount sử dụng fio
Test hiệu năng random read/write với 4k block size, job file:

    [global]
    name=test-1
    bs=4k
    ioengine=rbd
    pool=rbdpool1
    rbdname=disk02
    size=100m
    runtime=600
    rw=randwrite
    rwmixread=40

    [rbd_iodepth32]
    iodepth=32


Kết quả

    rbd_iodepth32: (groupid=0, jobs=1): err= 0: pid=1923: Fri Aug  6 14:44:24 2021
      write: IOPS=646, BW=2586KiB/s (2649kB/s)(53.2MiB/21076msec)
   
    Run status group 0 (all jobs):
      WRITE: bw=2586KiB/s (2649kB/s), 2586KiB/s-2586KiB/s (2649kB/s-2649kB/s), io=53.2MiB (55.8MB), run=21076-21076msec
    
    

    


# Triển khai Ceph Nautilus bằng ceph-deploy
## Mô hình
![](https://github.com/huynp1999/huynp/blob/master/pic/storage/nau/ceph6.PNG)

Mô hình IP

|  Host name | Management IP (ens33) | Public IP (ens34) | Cluster IP (ens35) | Disk |
| --- |:------:|:-----:|:-----:|:-----:|
|  ceph01   |  192.168.1.21    | 10.10.10.21 | 10.10.11.21 | 3 x 20GB (sda, sdb, sdc) |
|  ceph02   |   192.168.1.22   | 10.10.10.22 | 10.10.11.21 | 3 x 20GB (sda, sdb, sdc) |
|  ceph03   |   192.168.1.23   | 10.10.10.23 | 10.10.11.21 | 3 x 20GB (sda, sdb, sdc) |

## Triển khai trên 3 node
Sau khi đặt IP theo mô hình bên trên, khai báo trên cả 3 node các hostname trong `/etc/hosts` để về sau Ceph sẽ dựa vào đó để cấu hình và kết nối tới các node.

    cat << EOF > /etc/hosts
    10.10.10.21 ceph01
    10.10.10.22 ceph02
    10.10.10.23 ceph03
    EOF

Đồng bộ thời gian cho 3 node:

    apt install -y chrony
    
Tạo user `cephuser` và nhập mật khẩu

    sudo useradd -d /home/cephuser -m cephuser
    sudo passwd cephuser
    
Cấp quyền sudo cho `cephuser`

    echo "cephuser ALL = (root) NOPASSWD:ALL" | sudo tee /etc/sudoers.d/cephuser
    sudo chmod 0440 /etc/sudoers.d/cephuser

Khai báo repo của Ceph Nautilus

    # wget -q -O- 'https://download.ceph.com/keys/release.asc' | sudo apt-key add -
    OK
    # echo deb https://download.ceph.com/debian-nautilus/ $(lsb_release -sc) main | sudo tee /etc/apt/sources.list.d/ceph.list
    # apt update

## Sử dụng ceph-deploy trên ceph01
Đứng trên ceph01 (ceph-admin) để cài đặt ceph-deploy và thao tác với ceph02, ceph03 từ xa.

    apt install -y ceph-deploy
    
Từ đây sẽ chỉ làm việc bằng user `cephuser`

    su - cephuser
    
Tạo private key và public key cho user cephuser và copy sang các node còn lại

    ssh-keygen
    ssh-copy-id cephuser@ceph01
    ssh-copy-id cephuser@ceph02
    ssh-copy-id cephuser@ceph03
    
Tạo thư mục nơi sẽ chứa các file cấu hình khi cài đặt Ceph

    cd ~
    mkdir my-cluster
    cd my-cluster 
 
Khởi tạo các node ceph trong cluser.

    ceph-deploy new ceph01 ceph02 ceph03 
    
Sau khi khởi tạo, các file cấu hình sẽ được tạo ra trong thư mục hiện tại
    
    $ ls -alh
    total 24K
    drwxrwxr-x 2 cephuser cephuser 4.0K Aug  3 07:58 .
    drwxr-xr-x 6 cephuser cephuser 4.0K Aug  3 07:58 ..
    -rw-rw-r-- 1 cephuser cephuser  238 Aug  3 07:58 ceph.conf
    -rw-rw-r-- 1 cephuser cephuser 5.1K Aug  3 07:58 ceph-deploy-ceph.log
    -rw------- 1 cephuser cephuser   73 Aug  3 07:58 ceph.mon.keyring

Cấu hình file `ceph.conf` trước khi thực hiện cài đặt các gói cần thiết cho ceph trên các node
- Note: Các IP file `/etc/hosts` phải thuộc subnet của `public network`
```
cat << EOF >> ceph.conf
public network = 10.10.10.0/24
cluster network = 10.10.11.0/24
osd objectstore = bluestore
mon_allow_pool_delete = true
osd pool default size = 3
osd pool default min size = 1
EOF
```
Tiến hình cài đặt Ceph Nautilus trên các node

    ceph-deploy install --release nautilus ceph01 ceph02 ceph03
 
Khi cài đặt thành công thì sẽ có thể kiểm tra version của Ceph trên cả 3 node

    ceph -v
    ceph version 14.2.22 (ca74598065096e6fcbd8433c8779a2be0c889351) nautilus (stable)

### Thành phần Monitor
Thiết lập thành phần MON cho cả 3 node

    ceph-deploy mon create-initial
    
Khi thực hiện thành công, các 4 file keyring sẽ được thêm vào thư mục hiện tại `my-cluster`, có thể kiểm tra bằng `ls -l`

    ceph.bootstrap-mds.keyring
    ceph.bootstrap-mgr.keyring
    ceph.bootstrap-osd.keyring
    ceph.bootstrap-rgw.keyring
    
Thực hiện copy file `ceph.client.admin.keyring` sang các node trong cụm Ceph cluster. File này sẽ được copy vào thư mục `/etc/ceph/` trên các node.

    ceph-deploy admin ceph01 ceph02 ceph03

Đứng trên node ceph01 phân quyền cho file `/etc/ceph/ceph.client.admin.keyring` trên cả 03 node.

    ssh cephuser@ceph01 'sudo chmod +r /etc/ceph/ceph.client.admin.keyring'
    ssh cephuser@ceph02 'sudo chmod +r /etc/ceph/ceph.client.admin.keyring'
    ssh cephuser@ceph03 'sudo chmod +r /etc/ceph/ceph.client.admin.keyring'

Đứng trên node ceph01 và thực hiện khai báo các OSD disk. Bước này sẽ thực hiện format các disk trên cả 3 node và join chúng vào làm các OSD (Thành phần chứa dữ liệu của CEPH).

    ceph-deploy osd create --data /dev/sdb ceph01
    ceph-deploy osd create --data /dev/sdc ceph01

    ceph-deploy osd create --data /dev/sdb ceph02
    ceph-deploy osd create --data /dev/sdc ceph02

    ceph-deploy osd create --data /dev/sdb ceph03
    ceph-deploy osd create --data /dev/sdc ceph03

Có thể kiểm tra kết quả format này trên cả 3 node

    # lsblk
    NAME                                                                                                  MAJ:MIN RM  SIZE RO TYPE MOUNTPOINT
    sda                                                                                                     8:0    0   20G  0 disk
    ├─sda1                                                                                                  8:1    0    1M  0 part
    └─sda2                                                                                                  8:2    0   20G  0 part /
    sdb                                                                                                     8:16   0   20G  0 disk
    └─ceph--ebf59b56--1566--43b4--89b2--70ae1e812d30-osd--block--b576d34c--c70d--437f--89b3--27c42f30fe2b 253:0    0   20G  0 lvm
    sdc                                                                                                     8:32   0   20G  0 disk
    └─ceph--7cdb4054--1ebe--4821--9ac6--3f924aae6a3d-osd--block--08e6237a--6679--4519--a84f--088ccaec4452 253:1    0   20G  0 lvm

Kiểm tra tình của Ceph cluster

    $ ceph -s
      cluster:
        id:     022060cf-ee36-4476-9695-d18e86bda59e
        health: HEALTH_WARN
                no active mgr

      services:
        mon: 3 daemons, quorum ceph01,ceph02,ceph03 (age 103m)
        mgr: ceph01(active, since 93m)
        osd: 6 osds: 6 up (since 101m), 6 in (since 101m)
        rgw: 1 daemon active (ceph02)

      task status:

      data:
        pools:   4 pools, 128 pgs
        objects: 189 objects, 1.6 KiB
        usage:   6.0 GiB used, 114 GiB / 120 GiB avail
        pgs:     128 active+clean

Có thể thấy trạng thái sẽ là HEALTH_WARN, lý do là vì ceph-mgr chưa được tạo.

### Thành phần Manager 
Thực hiện trên node ceph01

    sudo apt install -y python-jwt python-routes
    
Cài đặt packet ceph-dashboad là `ceph-grafana-dashboards-14.2.22-1.el8.noarch.rpm` và `ceph-mgr-dashboard-14.2.22-1.el8.noarch.rpm`

    sudo rpm -Uvh http://centos-hcm.viettelidc.com.vn/8/storage/x86_64/ceph-nautilus/Packages/c/ceph-grafana-dashboards-14.2.22-1.el8.noarch.rpm
    sudo alien -i /home/cephuser/ceph-mgr-dashboard-14.2.22-1.el8.noarch.rpm --scripts



    radosgw-admin user create --uid=gwadmin --display-name=RadosGWAdmin --system


    "keys": [
        {
            "user": "gwadmin",
            "access_key": "XRDWUYAGFHWZVZ2P5ZYZ",
            "secret_key": "4DcDR3OxcZLpq0dGhOvWXLo8ghH5AdKEv3sC4FME"
        }
    ],

    ceph dashboard set-rgw-api-access-key -i ./acckey.txt
    ceph dashboard set-rgw-api-secret-key -i ./seckey.txt
    ceph dashboard set-rgw-api-ssl-verify False



# Triển khai Ceph Octopus bằng chephadm
## Mô hình

![](https://github.com/huynp1999/huynp/blob/master/pic/storage/ceph7.PNG)

Quy hoạch IP
|  Host name | Public IP | Cluster IP | Disk |
| --- |:------:|:-----:|:-----:|
|  Ceph01   |  192.168.1.51    | 10.10.10.51 | 3 x 20GB (sda, sdb, sdc) |
|  Ceph02   |   192.168.1.52   | 10.10.10.52 | 3 x 20GB (sda, sdb, sdc) |
|  Ceph03   |   192.168.1.53   | 10.10.10.53 | 3 x 20GB (sda, sdb, sdc) |


## Triển khai
Trước tiêm, các node cần phải được cài đặt những gói sau:
    
    python3
    Podman
    lvm2

#### Tải xuống file nhị phân cephadm và cấp quyền thực thi

    # curl --silent --remote-name --location https://github.com/ceph/ceph/raw/octopus/src/cephadm/cephadm
    # chmod +x cephadm

#### Sử dụng cephadm để thêm repo cần thiết

    # ./cephadm add-repo --release octopus

#### Cài đặt gói cephadm và binary sẽ được xuất hiện trong $PATH 
    
    # ./cephadm install
    # which cephadm
    /usr/sbin/cephadm
    
#### Cài đặt Ceph command line
Check công cụ cephadm đã có sẵn trên mỗi cluster và cài đặt gói `ceph-common` cho command `ceph` và gói `ceph-osd` trên các cluster

    # cephadm prepare-host
    # cephadm install ceph-common ceph-osd

Note: bước này có thể tốn khá nhiều thời gian trong quá trình cài đặt

#### Tạo thư mục dữ liệu cho Ceph để ghi các file cấu hình

    # mkdir -p /etc/ceph
    
#### Tạo một cluster mới
Bước đầu tiên để tạo một cụm Ceph cluster mới là chạy lệnh cephadm bootstrap trên máy chủ đầu tiên của cụm.

Command này sẽ tạo monitor daemon đầu tiên cho Ceph cluster.

    # cephadm bootstrap --mon-ip 192.168.1.51
    ...
    ...
    Ceph Dashboard is now available at:

                 URL: https://ceph01:8443/
                User: admin
            Password: 2lvtptdowr

Command này sẽ thực hiện:

- Tạo monitor và manager daemon trên máy chủ cục bộ cho cluster
- Tạo khóa SSH mới cho Ceph cluster và thêm nó vào `/root/.SSH/` được ủy quyền của người dùng gốc
- Ghi các cấu hình cơ bản vào `/etc/ceph/ceph.conf`
- Khởi động và cấu hình mgr và các mô-đun mgr
- Triển khai dashboard
- Ghi khóa đặc quyền quản lý client.admin vào `/etc/ceph/ceph.client.admin.keyring`
- Ghi khóa công khai vào `/etc/ceph/ceph.pub`

#### Thêm các host
Trước tiên cần phân phối khóa công khai ceph.pub đã được tạo bằng bootstrap

    # ssh-copy-id -f -i /etc/ceph/ceph.pub root@ceph02
    # ssh-copy-id -f -i /etc/ceph/ceph.pub root@ceph03
 
Add các osd

    # ceph orch host add ceph01 192.168.1.51
    Added host 'ceph01'
    # ceph orch host add ceph02 192.168.1.52
    Added host 'ceph02'
    # ceph orch host add ceph03 192.168.1.53
    Added host 'ceph03'

Kiểm tra:

    # ceph orch host ls
    HOST    ADDR          LABELS  STATUS
    ceph01  192.168.1.51
    ceph02  192.168.1.52
    ceph03  192.168.1.53

#### Add mon
Một Ceph cluster điển hình có ba hoặc năm monitor daemon được phân phối trên các máy chủ.

    # ceph orch apply mon "ceph01,ceph02,ceph03"

#### Triển khai OSD
Sau khi thêm các OSD, cephadm sẽ thu thập thông tin trên từng disk của các server.
Có thể thấy rằng đều có sẵn 2 đĩa trong mỗi server OSB , sda không có sẵn vì được dùng cho HĐH, cephadm sẽ tự tìm hiểu mà không cần phải cấu hình.

    # ceph orch device ls
    Hostname  Path      Type  Serial  Size   Health   Ident  Fault  Available
    ceph01    /dev/sdb  hdd           21.4G  Unknown  N/A    N/A    Yes
    ceph01    /dev/sdc  hdd           21.4G  Unknown  N/A    N/A    Yes
    ceph02    /dev/sdb  hdd           21.4G  Unknown  N/A    N/A    Yes
    ceph02    /dev/sdc  hdd           21.4G  Unknown  N/A    N/A    Yes
    ceph03    /dev/sdb  hdd           21.4G  Unknown  N/A    N/A    Yes
    ceph03    /dev/sdc  hdd           21.4G  Unknown  N/A    N/A    Yes
    
Theo như docs của Ceph thì để một thiết bị lưu trữ được coi là khả dụng thì phải đủ vài tiêu chí sau:

1. Thiết bị phải không có phân vùng
2. Thiết bị không được có bất kỳ trạng thái LVM nào
3. Thiết bị không được chứa filesystem
4. Thiết bị phải lớn hơn 5 GB 

#### Tạo OSD
Có nhiều cách để tạo OSD mới, apply này sẽ sử dụng tất cả các thiết bị lưu trữ có sẵn và chưa được sử dụng

    ceph orch apply osd --all-available-devices
    
#### Kiểm tra trạng thái của cluster

    # ceph -s
    cluster:
      id:     986a2e62-ed19-11eb-a2c3-000c298bbbb2
      health: HEALTH_OK

    services:
      mon: 3 daemons, quorum ceph01,ceph02,ceph03 (age 2m)
      mgr: ceph01.rpxmxr(active, since 10m), standbys: ceph02.tuitnm
      osd: 6 osds: 6 up (since 12s), 6 in (since 12s)

    data:
      pools:   1 pools, 1 pgs
      objects: 0 objects, 0 B
      usage:   6.0 GiB used, 114 GiB / 120 GiB avail
      pgs:     1 active+clean

Nếu xảy ra HEALTH_WARN MON_CLOCK_SKEW thì là do thời gian giữa các node chưa được đồng bộ, sử dụng:

    # apt install -y chrony
    
#### Kiểm tra dashboard
Điểm truy cập, tài khoản và mật khẩu được cung cấp trong quá trình bootstrap phía trên

Màn hình trạng thái tổng thể của Ceph cluster

![](https://github.com/huynp1999/huynp/blob/master/pic/storage/ceph1.PNG)

Màn hình thành phần MON

![](https://github.com/huynp1999/huynp/blob/master/pic/storage/ceph2.PNG)

Các OSD disk

![](https://github.com/huynp1999/huynp/blob/master/pic/storage/ceph3.PNG)



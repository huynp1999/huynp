# Setup tại 3 node
Setup repo, cài đặt packet và kiểm tra trên 3 node của cluster:
 
    [root@ceph01 ~]# yum install -y epel-release
    [root@ceph01 ~]# yum update -y
    
    [root@ceph01 ~]# cat <<EOF> /etc/yum.repos.d/ceph.repo
    [ceph]
    name=Ceph packages for $basearch
    baseurl=https://download.ceph.com/rpm-nautilus/el7/x86_64/
    enabled=1
    priority=2
    gpgcheck=1
    gpgkey=https://download.ceph.com/keys/release.asc

    [ceph-noarch]
    name=Ceph noarch packages
    baseurl=https://download.ceph.com/rpm-nautilus/el7/noarch
    enabled=1
    priority=2
    gpgcheck=1
    gpgkey=https://download.ceph.com/keys/release.asc

    [ceph-source]
    name=Ceph source packages
    baseurl=https://download.ceph.com/rpm-nautilus/el7/SRPMS
    enabled=0
    priority=2
    gpgcheck=1
    gpgkey=https://download.ceph.com/keys/release.asc
    EOF
    
    [root@ceph01 ~]# yum update -y
    [root@ceph01 ~]# yum install -y ceph
    
    [root@ceph01 ~]# ceph -v
    ceph version 14.2.22 (ca74598065096e6fcbd8433c8779a2be0c889351) nautilus (stable)
    
    [root@ceph01 ~]# rpm -qa | egrep -i "ceph|rados|rbd"
    python-ceph-argparse-14.2.22-0.el7.x86_64
    python-rados-14.2.22-0.el7.x86_64
    ceph-base-14.2.22-0.el7.x86_64
    ceph-osd-14.2.22-0.el7.x86_64
    ceph-14.2.22-0.el7.x86_64
    centos-release-ceph-nautilus-1.2-2.el7.centos.noarch
    librados2-14.2.22-0.el7.x86_64
    librbd1-14.2.22-0.el7.x86_64
    python-cephfs-14.2.22-0.el7.x86_64
    libradosstriper1-14.2.22-0.el7.x86_64
    ceph-common-14.2.22-0.el7.x86_64
    ceph-selinux-14.2.22-0.el7.x86_64
    ceph-mds-14.2.22-0.el7.x86_64
    ceph-mgr-14.2.22-0.el7.x86_64
    ceph-deploy-2.0.1-0.noarch
    libcephfs2-14.2.22-0.el7.x86_64
    python-rbd-14.2.22-0.el7.x86_64
    ceph-mon-14.2.22-0.el7.x86_64

Thêm các alias cho các node tại `/etc/hosts`:

    192.168.1.71 ceph01
    192.168.1.72 ceph02
    192.168.1.73 ceph03
    
    10.10.10.71 ceph01
    10.10.10.72 ceph02
    10.10.10.73 ceph03
# Cấu hình các thành phần tại node mon đầu tiên (ceph01) 
### Monitor
Tạo file cấu hình cho ceph, mặc định ở `/etc/ceph/ceph.conf`. Và generate uuid (fsid) cho cluster:

    [root@ceph01 ~]# touch /etc/ceph/ceph.conf
    [root@ceph01 ~]# uuidgen
    662560a5-5c3a-4ee5-a3d0-48ca6ae395ea

Cấu hình cơ bản sau khi tạo file:

    [root@ceph01 ~]# vim /etc/ceph/ceph.conf
    [global]
    fsid = 662560a5-5c3a-4ee5-a3d0-48ca6ae395ea
    mon initial members = ceph01
    mon host = 192.168.1.71,192.168.1.72,192.168.1.73
    auth cluster required = cephx
    auth service required = cephx
    auth client required = cephx
    
    public network = 192.168.1.0/24
    cluster network = 10.10.10.0/24
    osd objectstore = bluestore
    mon_allow_pool_delete = true
    osd pool default size = 3
    osd pool default min size = 1
    
Tạo keyring cho cluster và tạo một monitor secret key:
    
    [root@ceph01 ~]# ceph-authtool --create-keyring /tmp/ceph.mon.keyring --gen-key -n mon. --cap mon 'allow *'

Tạo admin keyring và add user `client.admin` vào key:

    [root@ceph01 ~]# ceph-authtool --create-keyring /etc/ceph/ceph.client.admin.keyring --gen-key -n client.admin --cap mon 'allow *' --cap osd 'allow *' --cap mds 'allow *' --cap mgr 'allow *'
    
Tạo bootstrap-osd keyring và add `client.bootstrap-osd` vào key:

    [root@ceph01 ~]# ceph-authtool --create-keyring /var/lib/ceph/bootstrap-osd/ceph.keyring --gen-key -n client.bootstrap-osd --cap mon 'profile bootstrap-osd' --cap mgr 'allow r'

Add 2 key vừa tạo vào monitor keyring:
    
    [root@ceph01 ~]# ceph-authtool /tmp/ceph.mon.keyring --import-keyring /etc/ceph/ceph.client.admin.keyring
    [root@ceph01 ~]# ceph-authtool /tmp/ceph.mon.keyring --import-keyring /var/lib/ceph/bootstrap-osd/ceph.keyring

Đổi owner cho monitor keyring:

    [root@ceph01 ~]# chown ceph:ceph /tmp/ceph.mon.keyring
    
Tạo monitor map cho monitor đầu tiên trong cluster, với hostname, ip, fsid vừa tạo và lưu vào `/tmp/monmap`:

    [root@ceph01 ~]# monmaptool --create --add ceph01 192.168.1.71 --fsid 662560a5-5c3a-4ee5-a3d0-48ca6ae395ea /tmp/monmap

Tạo thư mục dữ liệu cho monitor tại `/var/lib/ceph/mon/` với tên thư mục là `{cluster-name}-{hostname}`:

    [root@ceph01 ~]# mkdir /var/lib/ceph/mon/ceph-ceph01/

Add monitor map và keyring vào monitor daemon đầu tiên trong cluster:

    [root@ceph01 ~]# ceph-mon --mkfs -i ceph01 --monmap /tmp/monmap --keyring /tmp/ceph.mon.keyring

Đổi owner cho các directory vừa được tạo:
    
    [root@ceph01 ~]# chown -R ceph:ceph /var/lib/ceph/mon
    [root@ceph01 ~]# chown -R ceph:ceph /var/log/ceph
    [root@ceph01 ~]# chown -R ceph:ceph /var/run/ceph
    [root@ceph01 ~]# chown ceph:ceph /etc/ceph/ceph.client.admin.keyring
    [root@ceph01 ~]# chown ceph:ceph /etc/ceph/ceph.conf
    [root@ceph01 ~]# chown ceph:ceph /etc/ceph/rbdmap

Khởi động monitor daemon:

    [root@ceph01 ~]# systemctl enable ceph-mon.target
    [root@ceph01 ~]# systemctl enable ceph-mon@ceph01
    [root@ceph01 ~]# systemctl start ceph-mon@ceph01

Kiểm tra:

    [root@ceph01 ~]# ceph -s
      cluster:
        id:     662560a5-5c3a-4ee5-a3d0-48ca6ae395ea
        health: HEALTH_WARN
                mon is allowing insecure global_id reclaim
                1 monitors have not enabled msgr2

      services:
        mon: 1 daemons, quorum ceph01 (age 24s)
        mgr: no daemons active
        osd: 0 osds: 0 up, 0 in

Troubleshoot: nếu `ceph -s` không hoạt động và service `ceph-mon@ceph01` bị fail thì lỗi do phân quyền, owner của các thư mục.
### Manager
Tạo thư mục dữ liệu cho manager tại `/var/lib/ceph/mgr/` với tên thư mục là `{cluster-name}-{hostname}`:

    [root@ceph01 ~]# mkdir /var/lib/ceph/mgr/ceph-ceph01

Tạo auth key cho `ceph-mgr` daemon:

    [root@ceph01 ~]# ceph auth get-or-create mgr.`hostname -s` mon 'allow profile mgr' osd 'allow *' mds 'allow *' -o /var/lib/ceph/mgr/ceph-ceph01/keyring
    [root@ceph01 ~]# chown -R ceph:ceph /var/lib/ceph/mgr

Khởi động manager daemon:

    [root@ceph01 ~]# systemctl enable ceph-mgr.target
    [root@ceph01 ~]# systemctl enable ceph-mgr@ceph01
    [root@ceph01 ~]# systemctl start ceph-mgr@ceph01
    
Kiểm tra:

    [root@ceph01 ~]# ceph -s
      cluster:
        id:     662560a5-5c3a-4ee5-a3d0-48ca6ae395ea
        health: HEALTH_WARN
                mon is allowing insecure global_id reclaim
                1 monitors have not enabled msgr2

      services:
        mon: 1 daemons, quorum ceph01 (age 9m)
        mgr: ceph01(active, since 17s)
        osd: 0 osds: 0 up, 0 in

      data:
        pools:   0 pools, 0 pgs
        objects: 0 objects, 0 B
        usage:   0 B used, 0 B / 0 B avail

### OSD
Nếu node OSD nằm riêng với node mon thì phải copy admin keyring và config cho node OSD trước khi deploy trên đó:

    scp root@osd01:/etc/ceph/ceph.conf /etc/ceph
    scp root@osd01:/etc/ceph/ceph.client.admin.keyring /etc/ceph
    scp root@osd01:/var/lib/ceph/bootstrap-osd/ceph.keyring /var/lib/ceph/bootstrap-osd/ceph.keyring

Có 3 cách để deploy thủ công một OSD từ device, đây là cách nhanh nhất 2 cách còn lại có thể tham khảo ở các docs bên dưới. Sau khi đã có đủ config và các keyring cần thiết, triển khai osd trên thiết bị, ví dụ `/dev/sdb`:

    ceph-volume lvm create --data /dev/sdb
    
Kiểm tra:

    [root@ceph01 ~]# ceph -s
       cluster:
         id:     662560a5-5c3a-4ee5-a3d0-48ca6ae395ea
         health: HEALTH_WARN
                 OSD count 1 < osd_pool_default_size 3
                 mon is allowing insecure global_id reclaim
                 1 monitors have not enabled msgr2

       services:
         mon: 1 daemons, quorum ceph01 (age 42m)
         mgr: ceph01(active, since 32m)
         osd: 1 osds: 1 up (since 1.5389s), 1 in (since 1.5389s)

       data:
         pools:   0 pools, 0 pgs
         objects: 0 objects, 0 B
         usage:   1.0 GiB used, 19 GiB / 20 GiB avail
         pgs:

Do mới cluster mới có 1 osd < 3 (chỉ số replicate size đã được cấu hình trong `ceph.conf`) nên sẽ có warning. Chỉ cần deploy thêm osd tại các node khác là tự động hết.

Như vậy là đã xong node mon, mgr và osd đầu tiên.
# Deploy 2 node còn lại
### Monitor
Trước tiên cần copy config từ node đầu tiên:

    [root@ceph01 ~]# scp /etc/ceph/ceph.* ceph02:/etc/ceph
    [root@ceph01 ~]# scp /etc/ceph/ceph.* ceph03:/etc/ceph

Tại node `ceph02`, tạo thư mục dữ liệu cho monitor:

    [root@ceph02 ~]# mkdir /var/lib/ceph/mon/ceph-ceph02
    
Nhận keyring và monitor map từ monitor của node `ceph01`:

    [root@ceph02 ~]# ceph auth get mon. -o /tmp/monkeyring
    exported keyring for mon.
    [root@ceph02 ~]# ceph mon getmap -o /tmp/monmap
    got monmap epoch 1

Add monitor map và keyring vừa nhận được vào daemon của monitor thứ 2 trong cluster:

    [root@ceph02 ~]# ceph-mon -i ceph02 --mkfs --monmap /tmp/monmap --keyring /tmp/monkeyring
    
Khởi động monitor mới, nó sẽ tự động join vào cluster thông qua `--public-addr {ip}` hoặc `--public-network {network}`:  

    [root@ceph02 ~]# ceph-mon -i ceph02 --public-addr 192.168.1.72

Kiểm tra:

    # ceph -s
      cluster:
        id:     662560a5-5c3a-4ee5-a3d0-48ca6ae395ea
        health: HEALTH_WARN
                OSD count 2 < osd_pool_default_size 3
                mons are allowing insecure global_id reclaim
                1 monitors have not enabled msgr2

      services:
        mon: 2 daemons, quorum ceph01,ceph02 (age 13m)
        mgr: ceph01(active, since 55m)
        osd: 2 osds: 2 up (since 0.523146s), 2 in (since 0.523146s)

      data:
        pools:   0 pools, 0 pgs
        objects: 0 objects, 0 B
        usage:   1.0 GiB used, 19 GiB / 20 GiB avail
        pgs:

### OSD
Để deploy được OSD thì sẽ cần `bootstrap-osd keyring` mà đã được tạo ở node đầu tiên, copy sang node 2:

    [root@ceph01 ~]# scp /var/lib/ceph/bootstrap-osd/ceph.keyring root@ceph02:/var/lib/ceph/bootstrap-osd/ceph.keyring
    ceph.keyring                                                                                                        100%  129   186.0KB/s   00:00

Ở node 2 chỉ cần deploy osd tương tự:

    [root@ceph02 ~]# ceph-volume lvm create --data /dev/sdb
    [root@ceph02 ~]# ceph-volume lvm create --data /dev/sdc
    
Kiểm tra:
    
    # ceph -s
      cluster:
        id:     662560a5-5c3a-4ee5-a3d0-48ca6ae395ea
        health: HEALTH_WARN
                mons are allowing insecure global_id reclaim
                1 monitors have not enabled msgr2

      services:
        mon: 2 daemons, quorum ceph01,ceph02 (age 21m)
        mgr: ceph01(active, since 64m)
        osd: 4 osds: 4 up (since 2s), 4 in (since 2s)

      data:
        pools:   0 pools, 0 pgs
        objects: 0 objects, 0 B
        usage:   3.0 GiB used, 67 GiB / 70 GiB avail
        pgs:

### Manager
Tạo thư mục dữ liệu cho manager tại `/var/lib/ceph/mgr/` với tên thư mục là `{cluster-name}-{hostname}`:

    [root@ceph01 ~]# mkdir /var/lib/ceph/mgr/ceph-ceph01

Tạo auth key cho `ceph-mgr` daemon:

    [root@ceph01 ~]# ceph auth get-or-create mgr.`hostname -s` mon 'allow profile mgr' osd 'allow *' mds 'allow *' -o /var/lib/ceph/mgr/ceph-ceph01/keyring
    [root@ceph01 ~]# chown -R ceph:ceph /var/lib/ceph/mgr

Khởi động manager daemon:

    [root@ceph01 ~]# systemctl enable ceph-mgr.target
    [root@ceph01 ~]# systemctl enable ceph-mgr@ceph01
    [root@ceph01 ~]# systemctl start ceph-mgr@ceph01
    
Kiểm tra:

    # ceph -s
      cluster:
        id:     662560a5-5c3a-4ee5-a3d0-48ca6ae395ea
        health: HEALTH_WARN
                mons are allowing insecure global_id reclaim
                1 monitors have not enabled msgr2

      services:
        mon: 2 daemons, quorum ceph01,ceph02 (age 30m)
        mgr: ceph01(active, since 73m), standbys: ceph02
        osd: 4 osds: 4 up (since 9m), 4 in (since 9m)

      data:
        pools:   0 pools, 0 pgs
        objects: 0 objects, 0 B
        usage:   4.0 GiB used, 96 GiB / 100 GiB avail
        pgs:

 Làm tương tự các thành phần với node 3 còn lại.   

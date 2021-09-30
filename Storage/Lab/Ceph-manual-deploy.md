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

#Cấu hình các thành phần trong Ceph cluster
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

    chown ceph:ceph /tmp/ceph.mon.keyring
    
Tạo monitor map cho monitor đầu tiên trong cluster, với hostname, ip, fsid vừa tạo và lưu vào `/tmp/monmap`:

    monmaptool --create --add ceph01 10.10.10.71 --fsid 662560a5-5c3a-4ee5-a3d0-48ca6ae395ea /tmp/monmap

Tạo thư mục dữ liệu cho monitor tại `/var/lib/ceph/mon/` với tên thư mục là `{cluster-name}-{hostname}`:

    mkdir /var/lib/ceph/mon/ceph-ceph01/

Add monitor map và keyring vào monitor daemon đầu tiên trong cluster:

    sudo -u ceph ceph-mon --mkfs -i ceph01 --monmap /tmp/monmap --keyring /tmp/ceph.mon.keyring

Khởi động monitor daemon:

    systemctl start ceph-mon@ceph01


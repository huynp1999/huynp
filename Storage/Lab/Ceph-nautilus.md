
Theem repo

    # wget -q -O- 'https://download.ceph.com/keys/release.asc' | sudo apt-key add -
    OK


    $ ls -alh
    total 24K
    drwxrwxr-x 2 cephuser cephuser 4.0K Aug  3 07:58 .
    drwxr-xr-x 6 cephuser cephuser 4.0K Aug  3 07:58 ..
    -rw-rw-r-- 1 cephuser cephuser  238 Aug  3 07:58 ceph.conf
    -rw-rw-r-- 1 cephuser cephuser 5.1K Aug  3 07:58 ceph-deploy-ceph.log
    -rw------- 1 cephuser cephuser   73 Aug  3 07:58 ceph.mon.keyring
       
    cat << EOF >> ceph.conf
    public network = 10.10.10.0/24
    cluster network = 10.10.11.0/24
    osd objectstore = bluestore
    mon_allow_pool_delete = true
    osd pool default size = 3
    osd pool default min size = 1
    EOF
    

    ceph -v
    ceph version 14.2.22 (ca74598065096e6fcbd8433c8779a2be0c889351) nautilus (stable)
    
    ceph-deploy osd create --data /dev/sdb ceph01
    ceph-deploy osd create --data /dev/sdc ceph01

    ceph-deploy osd create --data /dev/sdb ceph02
    ceph-deploy osd create --data /dev/sdc ceph02

    ceph-deploy osd create --data /dev/sdb ceph03
    ceph-deploy osd create --data /dev/sdc ceph03


sudo rpm -Uvh http://centos-hcm.viettelidc.com.vn/8/storage/x86_64/ceph-nautilus/Packages/c/ceph-grafana-dashboards-14.2.22-1.el8.noarch.rpm

sudo rpm -Uvh http://centos-hcm.viettelidc.com.vn/8/storage/x86_64/ceph-nautilus/Packages/c/ceph-mgr-dashboard-14.2.22-1.el8.noarch.rpm

sudo alien -i /home/cephuser/ceph-mgr-dashboard-14.2.22-1.el8.noarch.rpm --scripts

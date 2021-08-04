
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


    ceph -v
    ceph version 14.2.22 (ca74598065096e6fcbd8433c8779a2be0c889351) nautilus (stable)
    
    
    mon_host = 192.168.1.21,192.168.1.22,192.168.1.23
    mon_host = 10.10.10.21,10.10.10.22,10.10.10.23
    
    ceph-deploy --overwrite-conf mon create ceph01 ceph02 ceph03
    ceph-deploy mon create-initial

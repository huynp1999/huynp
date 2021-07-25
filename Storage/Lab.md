    
    
    # cephadm bootstrap --mon-ip 192.168.1.51
    ...
    ...
    Ceph Dashboard is now available at:

                 URL: https://ceph01:8443/
                User: admin
            Password: 2lvtptdowr




    # ceph orch host add ceph02 192.168.1.52
    Added host 'ceph02'
    # ceph orch host add ceph03 192.168.1.53
    Added host 'ceph03'
    # ceph orch host add ceph01 192.168.1.51
    Added host 'ceph01'

    # ceph orch host ls
    HOST    ADDR          LABELS  STATUS
    ceph01  192.168.1.51
    ceph02  192.168.1.52
    ceph03  192.168.1.53


    # ceph orch device ls
    Hostname  Path      Type  Serial  Size   Health   Ident  Fault  Available
    ceph01    /dev/sdb  hdd           21.4G  Unknown  N/A    N/A    Yes
    ceph01    /dev/sdc  hdd           21.4G  Unknown  N/A    N/A    Yes
    ceph02    /dev/sdb  hdd           21.4G  Unknown  N/A    N/A    Yes
    ceph02    /dev/sdc  hdd           21.4G  Unknown  N/A    N/A    Yes
    ceph03    /dev/sdb  hdd           21.4G  Unknown  N/A    N/A    Yes
    ceph03    /dev/sdc  hdd           21.4G  Unknown  N/A    N/A    Yes
    
    
    ceph orch apply osd --all-available-devices
    
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

    radosgw-admin user create --uid=huy123 --display-name=Huy --system
    ...
    ...
    "keys": [
        {
            "user": "huy123",
            "access_key": "F26WYJ8HWB6EGUXGAJ6M",
            "secret_key": "vpsit39Gyk37fCnr0a4g4obULqD8XaC0eFr0AVVF"
        }
    ],





    MON_CLOCK_SKEW apt install -y chrony
    

# Deploy cluster

    yum install epel-release -y
    yum install ansible git virtualenv -y

    pip3 install netaddr
    
Tạo user ansibledeploy trên 3 host và cấp quyền sudo:

    echo "ansibledeploy ALL = (root) NOPASSWD:ALL" | sudo tee /etc/sudoers.d/ansibledeploy
    chmod 0440 /etc/sudoers.d/ansibledeploy
    sed -i s'/Defaults requiretty/#Defaults requiretty'/g /etc/sudoers
    
cấu hình cho OSD, MON, MGR, RGW [firewall](https://access.redhat.com/documentation/en-us/red_hat_ceph_storage/3/html/installation_guide_for_red_hat_enterprise_linux/requirements-for-installing-rhcs#configuring-a-firewall-for-red-hat-ceph-storage-install)

    192.168.1.31 ceph01
    192.168.1.32 ceph02
    192.168.1.33 ceph03

chuyển user deploy
    
    [ansibledeploy@ceph01 root]$ ssh-keygen
    Generating public/private rsa key pair.
    Enter file in which to save the key (/home/ansibledeploy/.ssh/id_rsa):
    Created directory '/home/ansibledeploy/.ssh'.
    Enter passphrase (empty for no passphrase):
    Enter same passphrase again:
    Your identification has been saved in /home/ansibledeploy/.ssh/id_rsa.
    Your public key has been saved in /home/ansibledeploy/.ssh/id_rsa.pub.
    The key fingerprint is:
    SHA256:S3HfnUlR6q6SPoOQVInqmTZ7vnYJRiyJj+R/5F+rH8c ansibledeploy@ceph01
    The key's randomart image is:
    +---[RSA 3072]----+
    |       . .     .o|
    |      . o      ..|
    |   . + .. .   .. |
    |  o + +  o . o..o|
    | o + * .S   . oo.|
    |  o B *. . . .   |
    |   o * o.oo.E .  |
    |    o = +.=+ .   |
    |     =o+o+++.    |
    +----[SHA256]-----+

    [ansibledeploy@ceph01 root]$ vi  ~/.ssh/config
    Host ceph01
            Hostname ceph01
            user ansibledeploy
    Host ceph02
            Hostname ceph02
            user ansibledeploy
    Host ceph03
            Hostname ceph03
            user ansibledeploy
            
            
           
    [admin@host ~]$ mkdir ~/ceph-ansible-keys

    [root@ceph01 ~]# mkdir /var/log/ansible
    [root@ceph01 ~]# chown ansibledeploy.ansibledeploy /var/log/ansible
    [root@ceph01 ~]# chmod 755 /var/log/ansible
    
    [ansibledeploy@ceph01 root]$ ssh-keyscan ceph01 ceph02 ceph03 >> ~/.ssh/known_hosts
    # ceph02:22 SSH-2.0-OpenSSH_8.0
    # ceph01:22 SSH-2.0-OpenSSH_8.0
    # ceph01:22 SSH-2.0-OpenSSH_8.0
    # ceph01:22 SSH-2.0-OpenSSH_8.0
    # ceph02:22 SSH-2.0-OpenSSH_8.0
    # ceph02:22 SSH-2.0-OpenSSH_8.0
    # ceph03:22 SSH-2.0-OpenSSH_8.0
    # ceph03:22 SSH-2.0-OpenSSH_8.0
    # ceph03:22 SSH-2.0-OpenSSH_8.0
    
    [ansibledeploy@ceph01 root]$ chmod 600 ~/.ssh/config

Làm lần lượt với từng host:

    [ansibledeploy@ceph01 root]$ ssh-copy-id ansibledeploy@ceph01
    /usr/bin/ssh-copy-id: INFO: Source of key(s) to be installed: "/home/ansibledeploy/.ssh/id_rsa.pub"
    /usr/bin/ssh-copy-id: INFO: attempting to log in with the new key(s), to filter out any that are already installed
    /usr/bin/ssh-copy-id: INFO: 1 key(s) remain to be installed -- if you are prompted now it is to install the new keys
    ansibledeploy@ceph01's password:

    Number of key(s) added: 1

    Now try logging into the machine, with:   "ssh 'ansibledeploy@ceph01'"
    and check to make sure that only the key(s) you wanted were added.

    [ansibledeploy@ceph01 root]$ vi /etc/ansible/hosts
    ...
    [mons]
    ceph01
    ceph02
    ceph03
    [mgrs]
    ceph01
    ceph02
    ceph03
    [osds]
    ceph01
    ceph02
    ceph03   
    
Clone

    [root@ceph01 ~]# cd /usr/share
    [root@ceph01 share]# git clone https://github.com/ceph/ceph-ansible.git
    Cloning into 'ceph-ansible'...
    remote: Enumerating objects: 61727, done.
    remote: Counting objects: 100% (1194/1194), done.
    remote: Compressing objects: 100% (533/533), done.
    remote: Total 61727 (delta 877), reused 806 (delta 634), pack-reused 60533
    Receiving objects: 100% (61727/61727), 11.73 MiB | 8.76 MiB/s, done.
    Resolving deltas: 100% (43004/43004), done.
    [root@ceph01 share]# cd ceph-ansible/
    [root@ceph01 ceph-ansible]# git checkout stable-4.0
    Branch 'stable-4.0' set up to track remote branch 'stable-4.0' from 'origin'.
    Switched to a new branch 'stable-4.0'
    
Cấu hình

    [root@ceph01 ceph-ansible]# ln -s /usr/share/ceph-ansible/group_vars /etc/ansible/group_vars
    [root@ceph01 ceph-ansible]# cd /etc/ansible/group_vars/
    [root@ceph01 group_vars]# cp all.yml.sample all.yml

Cấu hình

    ceph_origin: repository
    ceph_repository: community
    ceph_stable_release: nautilus
    monitor_interface: ens33
    public_network: 192.168.1.0/24
    cluster_network: 10.10.10.0/24
    osd_objectstore: bluestore
    devices:
      - /dev/sdb
      - /dev/sdc
    dashboard_enabled: False
    
    ceph_conf_overrides:
      global:
        osd_pool_default_size: 3
        osd_pool_default_min_size: 2
        osd_pool_default_crush_rule: 0
        osd_pool_default_pg_num: 32
        osd_pool_default_pgp_num: 32

Pre deploy

    [root@ceph01 group_vars]# touch /var/log/ansible.log
    [root@ceph01 group_vars]# chown ansibledeploy:ansibledeploy /var/log/ansible.log
    [root@ceph01 group_vars]# chmod 775 /var/log/ansible.log
Sửa lại

    [root@ceph01 group_vars]# vi /etc/ansible/ansible.cfg
    ...
    action_plugins = /usr/share/ceph-ansible/plugins/actions/

Tiến hành deploy

    [root@ceph01 group_vars]# su ansibledeploy
    [ansibledeploy@ceph01 group_vars]$ cd /usr/share/ceph-ansible/
    [ansibledeploy@ceph01 ceph-ansible]$ sudo cp site.yml.sample site.yml
    [ansibledeploy@ceph01 ceph-ansible]$ ansible-playbook site.yml
    
Kết quả

    TASK [show ceph status for cluster ceph] ********************************************************************************
    Thursday 09 September 2021  15:40:58 +0700 (0:00:00.683)       14:42:22.836 ***
    ok: [ceph01 -> ceph01] =>
      msg:
      - '  cluster:'
      - '    id:     892df4ed-93b2-4338-9481-435dab49e281'
      - '    health: HEALTH_WARN'
      - '            mons are allowing insecure global_id reclaim'
      - ' '
      - '  services:'
      - '    mon: 3 daemons, quorum ceph01,ceph02,ceph03 (age 2m)'
      - '    mgr: ceph03(active, since 68s), standbys: ceph02, ceph01'
      - '    osd: 6 osds: 6 up (since 24s), 6 in (since 24s)'
      - ' '
      - '  task status:'
      - ' '
      - '  data:'
      - '    pools:   0 pools, 0 pgs'
      - '    objects: 0 objects, 0 B'
      - '    usage:   6.0 GiB used, 114 GiB / 120 GiB avail'
      - '    pgs:     '
      - ' '

    PLAY RECAP ***************************************************************************************************************
    ceph01                     : ok=314  changed=43   unreachable=0    failed=0    skipped=564  rescued=0    ignored=0
    ceph02                     : ok=268  changed=36   unreachable=0    failed=0    skipped=538  rescued=0    ignored=0
    ceph03                     : ok=277  changed=40   unreachable=0    failed=0    skipped=524  rescued=0    ignored=0

    INSTALLER STATUS *********************************************************************************************************
    Install Ceph Monitor           : Complete (0:00:33)
    Install Ceph Manager           : Complete (0:01:11)
    Install Ceph OSD               : Complete (0:00:59)
    Install Ceph Crash             : Complete (0:00:12)


# Add node


    PLAY RECAP ***************************************************************************************************************************************
    client01                   : ok=95   changed=10   unreachable=0    failed=0    skipped=309  rescued=0    ignored=0


    INSTALLER STATUS *********************************************************************************************************************************
    Install Ceph Client            : Complete (0:00:07)

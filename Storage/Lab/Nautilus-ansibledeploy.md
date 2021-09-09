# Deploy Ceph cluster bằng Ansible
## Làm việc với 3 node:

Mô hình IP:
|  Host name | Management IP (ens33) | Public IP (ens34) | Disk |
| --- |:------:|:-----:|:-----:|
|  ceph01   |  192.168.1.31    | 10.10.10.31 | 3 x 20GB (sda, sdb, sdc) |
|  ceph02   |   192.168.1.32   | 10.10.10.32 | 3 x 20GB (sda, sdb, sdc) |
|  ceph03   |   192.168.1.33   | 10.10.10.33 | 3 x 20GB (sda, sdb, sdc) |
  
Tạo user ansibledeploy trên 3 host và cấp quyền sudo:

    echo "ansibledeploy ALL = (root) NOPASSWD:ALL" | sudo tee /etc/sudoers.d/ansibledeploy
    chmod 0440 /etc/sudoers.d/ansibledeploy
    sed -i s'/Defaults requiretty/#Defaults requiretty'/g /etc/sudoers
    
(Optional) cấu hình firewall cho các node [firewall](https://access.redhat.com/documentation/en-us/red_hat_ceph_storage/3/html/installation_guide_for_red_hat_enterprise_linux/requirements-for-installing-rhcs#configuring-a-firewall-for-red-hat-ceph-storage-install)

## Làm việc tại node admin (ceph01)

Khai báo hostname cho 3 host trong `/etc/hosts`
    
    ...
    192.168.1.31 ceph01
    192.168.1.32 ceph02
    192.168.1.33 ceph03

Chuyển sang user `ansibledeploy`, tạo private key và public key cho user ansibledeploy và copy sang các node còn lại:
    
    [ansibledeploy@ceph01 root]$ ssh-keygen
    [ansibledeploy@ceph01 root]$ ssh-copy-id ansibledeploy@ceph01
    [ansibledeploy@ceph01 root]$ ssh-copy-id ansibledeploy@ceph02
    [ansibledeploy@ceph01 root]$ ssh-copy-id ansibledeploy@ceph03

Nếu copy bị lỗi về permission:

    [ansibledeploy@ceph01 root]$ chmod 600 ~/.ssh/config

Tạo ceph-ansible-keys và ansible log directory:

    [admin@host ~]$ mkdir ~/ceph-ansible-keys
    [root@ceph01 ~]# mkdir /var/log/ansible
    [root@ceph01 ~]# chown ansibledeploy.ansibledeploy /var/log/ansible
    [root@ceph01 ~]# chmod 755 /var/log/ansible

Cấu hình ansible inventory, mặc định ở `/etc/ansible/hosts`

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
    
Clone repo của Ceph và chuyển đang branch `stable-4.0` tức phiên bản `Nautilus`

    [root@ceph01 ~]# cd /usr/share
    [root@ceph01 share]# git clone https://github.com/ceph/ceph-ansible.git
    [root@ceph01 share]# cd ceph-ansible/
    [root@ceph01 ceph-ansible]# git checkout stable-4.0
    Branch 'stable-4.0' set up to track remote branch 'stable-4.0' from 'origin'.
    Switched to a new branch 'stable-4.0'
   
Tạo các file cấu hình:

    [root@ceph01 ceph-ansible]# ln -s /usr/share/ceph-ansible/group_vars /etc/ansible/group_vars
    [root@ceph01 ceph-ansible]# cd /etc/ansible/group_vars/
    [root@ceph01 group_vars]# cp all.yml.sample all.yml

Cấu hình `/etc/ansible/group_vars/all.yml`:

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

Các trường thông tin:

- ceph_origin — nguồn gốc của package, trong trường hợp này là repository.
- ceph_repository — phiên bản của repository
- ceph_stable_release — phiên bản của Ceph
- monitor_interface — interface mà ceph monitor sử dụng, cũng là interface của public_network
- public_network — mạng truy cập ra ngoài
- cluster_network — mạng dành cho việc replicate trong cluster
- osd_objectstore — filestore hoặc bluestore
- devices — các disk được sử dụng
- Ngoài ra còn có dedicated_devices — dành cho journal disk, ssd

Một vài cấu hình trước khi tiến hành deploy:

    [root@ceph01 group_vars]# touch /var/log/ansible.log
    [root@ceph01 group_vars]# chown ansibledeploy:ansibledeploy /var/log/ansible.log
    [root@ceph01 group_vars]# chmod 775 /var/log/ansible.log
    [root@ceph01 group_vars]# vi /etc/ansible/ansible.cfg
    ...
    action_plugins = /usr/share/ceph-ansible/plugins/actions/

Tiến hành deploy:

    [root@ceph01 group_vars]# su ansibledeploy
    [ansibledeploy@ceph01 group_vars]$ cd /usr/share/ceph-ansible/
    [ansibledeploy@ceph01 ceph-ansible]$ sudo cp site.yml.sample site.yml
    [ansibledeploy@ceph01 ceph-ansible]$ ansible-playbook site.yml
    
Kết quả khi deploy thành công:

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

# Thêm node mới vào cluster có sẵn
Ví dụ muốn thêm một hostname client có ip `192.168.1.35`:

    [root@ceph01 ceph-ansible]# vi /etc/hosts
    192.168.1.31 ceph01
    192.168.1.32 ceph02
    192.168.1.33 ceph03
    192.168.1.35 client01
    
Thêm node client vào inventory:

    [root@ceph01 ceph-ansible]# vi /etc/ansible/hosts
    ...
    [clients]
    client01
    
Tại node client, tạo và cấp quyền cho user ansibledeploy:

    echo "ansibledeploy ALL = (root) NOPASSWD:ALL" | sudo tee /etc/sudoers.d/ansibledeploy
    chmod 0440 /etc/sudoers.d/ansibledeploy
    sed -i s'/Defaults requiretty/#Defaults requiretty'/g /etc/sudoers

Quay lại admin node, cấp phát ssh key cho client:

    [ansibledeploy@ceph01 root]$ ssh-copy-id ansibledeploy@client01
    
Và playbook với option `--limit` riêng cho `client01`:

    [ansibledeploy@ceph01 ceph-ansible]$ ansible-playbook site.yml --limit client01

Kết quả khi deploy thành công:

    PLAY RECAP ***************************************************************************************************************************************
    client01                   : ok=95   changed=10   unreachable=0    failed=0    skipped=309  rescued=0    ignored=0


    INSTALLER STATUS *********************************************************************************************************************************
    Install Ceph Client            : Complete (0:00:07)
    
Kiểm tra tại node client:

    [root@client ~]# cat /etc/ceph/ceph.conf 
    # Please do not change this file directly since it is managed by Ansible and will be overwritten
    [global]
    fsid = c9e1807a-56fd-472b-aced-9479273d18a6
    mon host = 192.168.1.31,192.168.1.32,192.168.1.33
    public network = 192.168.1.0/24
    cluster network = 10.10.10.0/24
    [client.libvirt]
    admin socket = /var/run/ceph/$cluster-$type.$id.$pid.$cctid.asok # must be writable by QEMU and allowed by SELinux or AppArmor
    log file = /var/log/ceph/qemu-guest-$pid.log # must be writable by QEMU and allowed by SELinux or AppArmor

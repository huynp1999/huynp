

    [Unit]
    Description=Ceph object storage daemon osd.%i
    PartOf=ceph-osd.target
    After=network-online.target local-fs.target time-sync.target
    Before=remote-fs-pre.target ceph-osd.target
    Wants=network-online.target local-fs.target time-sync.target remote-fs-pre.target ceph-osd.target

    [Service]
    LimitNOFILE=1048576
    LimitNPROC=1048576
    EnvironmentFile=-/etc/default/ceph                                                              #lấy biến cache size=128Mib trong file
    Environment=CLUSTER=ceph                                                                        #đặt biến tên Cluster=ceph
    ExecStart=/usr/bin/ceph-osd -f --cluster ${CLUSTER} --id %i --setuser ceph --setgroup ceph      #lệnh khởi chạy service, bao gồm đường dẫn lệnh /usr/bin/ceph-osd và các arg để tuỳ chỉnh service. Ví dụ ${CLUSTER} là tên cluster, %i là id của osd
    ExecStartPre=/usr/lib/ceph/ceph-osd-prestart.sh --cluster ${CLUSTER} --id %i                    #lệnh bổ sung được thực hiện trước lệnh ExecStart, script prestart sẽ được làm rõ bên dưới
    ExecReload=/bin/kill -HUP $MAINPID                                                              #option -HUP của lệnh kill có ý nghĩa reload process theo PID
    LockPersonality=true                                                                            
    MemoryDenyWriteExecute=true
    # Need NewPrivileges via `sudo smartctl`
    NoNewPrivileges=false                                                                           #không nhận thêm privileges khác ngoài những gì đã được config tại đây
    ProtectControlGroups=true                                                                       #bật read-only tới tất cả process của unit
    ProtectHome=true                                                                                #process của unit không được tiếp cận tới /home, /root và /run/user
    ProtectKernelModules=true                                                                       .....
    # flushing filestore requires access to /proc/sys/vm/drop_caches                                .....
    ProtectKernelTunables=false
    ProtectSystem=full
    PrivateTmp=true
    TasksMax=infinity
    Restart=on-failure
    StartLimitInterval=30min
    StartLimitBurst=3

    [Install]
    WantedBy=ceph-osd.target


File `/usr/lib/ceph/ceph-osd-prestart.sh`

    #!/bin/sh

    # lấy arg được đẩy từ ExecStartPre= của systemd, --cluster ${CLUSTER} là tên cluster (mặc định: ceph), --id %i là id của osd
    if [ `uname` = FreeBSD ]; then
      GETOPT=/usr/local/bin/getopt
    else
      GETOPT=getopt
    fi

    eval set -- "$(${GETOPT} -o i: --long id:,cluster: -- $@)"

    while true ; do
            case "$1" in
                    -i|--id) id=$2; shift 2 ;;
                    --cluster) cluster=$2; shift 2 ;;
                    --) shift ; break ;;
            esac
    done

    if [ -z "$id"  ]; then
        echo "Usage: $0 [OPTIONS]"
        echo "--id/-i ID        set ID portion of my name"
        echo "--cluster NAME    set cluster name (default: ceph)"
        exit 1;
    fi
    
    # set đường dẫn của data dir với ceph-$id tức là id của từng osd
    data="/var/lib/ceph/osd/${cluster:-ceph}-$id"
    
    # kiểm tra data dir có tồn tại không
    # assert data directory exists - see http://tracker.ceph.com/issues/17091
    if [ ! -d "$data" ]; then
        echo "OSD data directory $data does not exist; bailing out." 1>&2
        exit 1
    fi
    
    # set đường dẫn của journal trong data dir
    journal="$data/journal"
    
    # check journal đã có trong data dir chưa (Filestore)
    if [ -L "$journal" -a ! -e "$journal" ]; then
        udevadm settle --timeout=5 || :
        if [ -L "$journal" -a ! -e "$journal" ]; then
            echo "ceph-osd(${cluster:-ceph}-$id): journal not present, not starting yet." 1>&2
            exit 0
        fi
    fi
    
    # check data dir có thuộc quyền sở hữu của user ceph hoặc root không
    # ensure ownership is correct
    owner=`stat -c %U $data/.`
    if [ $owner != 'ceph' -a $owner != 'root' ]; then
        echo "ceph-osd data dir $data is not owned by 'ceph' or 'root'"
        echo "you must 'chown -R ceph:ceph ...' or similar to fix ownership"
        exit 1
    fi

    exit 0



















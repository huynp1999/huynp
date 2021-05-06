# Run levels
Khi máy tính khởi động trải qua nhiều bước, kernel sẽ chạy chương trình đầu tiên với PID 1 - có tên chung là init. 

Gồm có 7 level vận hành tiêu chuẩn trong hệ thống linux:
0. Halt: tắt máy
1. Single user mode: chỉ duy nhất một user được phép kết nối hệ thống
2. Multi-user, without NFS: đa người dùng, không hỗ trợ networking
3. Full multi-user mode: đa người dùng, hỗ trợ networking
4. Unused
5. X11: sử dụng GUI desktop
6. Reboot: khởi động lại hệ thống

Tuy nhiên gần đây Ubuntu đã thay thế bằng systemd với tốc độ vận hành cao hơn, nhưng các chức năng tương tự:

5 graphic.target



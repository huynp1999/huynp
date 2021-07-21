## So sánh hiệu năng ghi giữa direct và sync I/O

Note: O_DIRECT yêu cầu cụ thể độ dài và địa chỉ căn chỉnh dành cho user-space buffer (không phải kernel buffer).
Cụ thể trong test này, buffer được căn chỉnh là 512, và dung lượng của nó phải là bội của 512. (ví dụ 64*512 = 65536)

**Kết quả**:

Khi so sánh kết quả đầu ra:

    ./direct.out /home/huynp/C/systemcall/benchmarkDirect/test 200 65536
    Write rate: 66MB/s
    Execute time: 3s

Program sử dụng `O_DIRECT` cho kết quả nhanh hơn hẳn khi sử dụng `O_SYNC`

    ./sync.out /home/huynp/C/systemcall/benchmarkSync/test 200 65536
    Write rate: 2MB/s
    Execute time: 89s
    
Dung lượng user buffer càng cao sẽ cho tốc độ ghi càng cao và ngược lại.

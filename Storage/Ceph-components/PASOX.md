# Thuật toán PAXOS
Trong một mạng lưới, để đánh giá như nào là một tiến trình lỗi cần dựa trên kết quả đánh giá của đa số các tiến trình khác.
PAXOS ra đời nhằm giải quyết quá trình đánh giá này.
Một tiến trình được coi là lỗi khi có nhiều hơn một nửa các tiến trình công nhận (lý do có thể do mất kết nối, không hoạt động, v.v)

## Các định nghĩa
Có 3 role mà các tiến trình (process) có thể có:
- `proposer`: là process đề xuất các giá trị. Đa số thời gian, chỉ có một process đóng vai trò `proposer`, như vậy cũng được gọi là leader
- `acceptor`: `acceptor` có thể accept các giá trị đề xuất. Một tập hợp các acceptor được gọi là quorum. Khi một đề xuất đã được chấp nhận bởi quorum, có nghĩa là đề xuất này đã được chọn.
- `learner`: sau khi đề xuất được chọn, `proposer` thông báo giá trị đến xuất đến cho các process, các process đó được gọi là `learner`.

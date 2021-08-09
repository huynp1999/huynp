# Thuật toán PAXOS
Trong một mạng lưới, để đánh giá như nào là một tiến trình lỗi cần dựa trên kết quả đánh giá của đa số các tiến trình khác.
PAXOS ra đời nhằm giải quyết quá trình đánh giá này.
- Một process được coi là failure khi có nhiều hơn một nửa các processes nhận thấy rằng process đó đã failure (lý do có thể do mất kết nối, không running, etc)

## Các định nghĩa
- Có 3 roles mà các tiến trình có thể có: `proposer`,  `acceptor` và `learner`.
	- `proposer`: là process đề xuất các giá trị. Đa số thời gian, chỉ có một process đóng vai trò `proposer`, như vậy cũng được gọi là leader
	- `acceptor`: `acceptor` có thể accept các giá trị đề xuất. Một tập hợp các chấp nhận đại diện cho đa số được gọi là quorum. Khi một đề xuất đã được chấp nhận bởi quorum, chúng ta nói rằng đề xuất này đã được chọn. Có nghĩa là khi một đề xuất được accept bởi đa số các processes (hơn một nửa) thì đề xuất đó đã được chọn.
	- `learner`: sau khi đề xuất được chọn, `proposer` thông báo giá trị đến xuất đến cho các processes, các processes đó được gọi là `learner`.

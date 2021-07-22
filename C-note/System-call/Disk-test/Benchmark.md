O_SYNC

| Buffer size | Write rate | Write time |
| --- |:------:|:-----:|
| 40MB    |    38MB/s | 1s |
| 80MB    |     38MB/s | 2s |
| 128MB    |     30.50MB/s | 4s |
| 512MB    |     32.53MB/s | 15s |
| 1GB    |    31.77MB/s | 30s |
| 2GB    |    32.88MB/s | 58s |

O_DSYNC

| Buffer size | Write rate | Write time |
| --- |:------:|:-----:|
| 40MB    |     38MB/s | 1s |
| 80MB    |     73MB/s | 1s |
| 128MB    |     61MB/s | 2s |
| 512MB    |     61MB/s | 8s |
| 1GB    |     50.16MB/s | 19s |
| 2GB    |    30.12 MB/s | 63s |

O_DIRECT

| Buffer size | Write rate | Write time |
| --- |:------:|:-----:|
| 40MB    |    40MB/s | >1s |
| 80MB    |     76MB/s | 1s |
| 128MB    |     61MB/s | 2s |
| 512MB    |     54.22MB/s | 9s |
| 1GB    |     59.56MB/s | 16s |
| 2GB    |     50.18MB/s | 39s |


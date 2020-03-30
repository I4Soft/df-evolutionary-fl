# Data-flow-based Evolutionary Fault Localization
This repository contains some complementary material to the work reported in the paper:
Data-flow-based Evolutionary Fault Localization https://dl.acm.org/doi/abs/10.1145/3341105.3373946.

Published in the The 35th ACM/SIGAPP Symposium On Applied Computing.
A video-presentation may be accessed in https://www.youtube.com/watch?v=2917Xt2IJgc


### Siemens Suite
Each program in the folder /Siemens_Suite have the original, and the instrumented version.
The instrumented version print logs about control- and data-flow elements executed.
From the logs is possible to obtain nodes and def-use associations covered in the execution of test cases. 



### Citation
```
@inproceedings{10.1145/3341105.3373946,
author = {Silva-Junior, Deuslirio and Leitao-Junior, Plinio S. and Dantas, Altino and Camilo-Junior, Celso G. and Harrison, Rachel},
title = {Data-Flow-Based Evolutionary Fault Localization},
year = {2020},
isbn = {9781450368667},
publisher = {Association for Computing Machinery},
address = {New York, NY, USA},
url = {https://doi.org/10.1145/3341105.3373946},
doi = {10.1145/3341105.3373946},
booktitle = {Proceedings of the 35th Annual ACM Symposium on Applied Computing},
pages = {1963–1970},
numpages = {8},
keywords = {SBSE, software debugging, data-flow analysis, fault localization},
location = {Brno, Czech Republic},
series = {SAC ’20}
}
```
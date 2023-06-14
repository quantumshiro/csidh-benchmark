# csidh-benchmark

# Requirements
- clang
- clnag++
- google benchmark

google benchmark can be installed as follows

```
sudo apt update
sudo apt install libbenchmark-dev
```
or
```
git clone https://github.com/google/benchmark googlebenchmark
cd googlebenchmark
git checkout v1.8.0 
cmake -DCMAKE_BUILD_TYPE=Release . 
make 
sudo make install
```


The same applies to clang, which is also available in apt.
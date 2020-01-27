# libjumanpp

libjumanpp is a shared library of [Jumanpp](https://github.com/ku-nlp/jumanpp) for C ++.


## Requirements

* Eigen (http://eigen.tuxfamily.org/index.php?title=Main_Page) -- linear algebra and matrix operations
* PEGTL (https://github.com/ColinH/PEGTL) -- Parser generator library
* Pathie (https://github.com/Quintus/pathie-cpp) -- A library for Unicode path management

## Building libjumanpp

```
$ cd libjumanpp
$ mkdir build
$ cd build
$ cmake .. -DCMAKE_BUILD_TYPE=Release
$ make -j $(nproc)
$ sudo make install
```

## Class synopsis

```c++
croco::Jumanpp {
public:
    typedef struct _node {
        std::string surface;
        std::string reading;
        std::string baseform;
        std::string pos;
        std::string subpos;
        std::string conjType;
        std::string conjForm;
        std::string feat;
        std::string redirect;
        int32_t posId;
        int32_t subposId;
        int32_t conjTypeId;
        int32_t conjFormId;
        int32_t featflag;
    } Node;

public:
    Jumanpp(std::string modelpath);
    std::vector<Node> analyze(std::string data);
    std::string wakati(std::string data);
}
```

## Table of Contents

[Jumanpp::Jumanpp](#__construct)  
[Jumanpp::analyze](#analyze)  
[Jumanpp::wakati](#wakati)  

-----

### <a name="__construct">Jumanpp::Jumanpp()

Load a model.

```c++
#include <jumanpp/jumanpp.h>

croco::Jumanpp jpp("/usr/local/libexec/jumanpp/jumandic.jppmdl");
```

-----

### <a name="analyze">std::vector<croco::Jumanpp::Node> Jumanpp::analyze(std::string text)

get the analyzed.

```c++
std::string input("このアボガドには魅力がたっぷりと詰まっている。");
std::vector<croco::Jumanpp::Node> nodes = jpp.analyze(input);

for (auto &node : nodes) {
    std::cout << node.surface
              << "::" << node.reading
              << " " << node.baseform
              << " " << node.pos << " " << node.posId
              << " " << node.subpos << " " << node.subposId
              << " " << node.conjType << " " << node.conjTypeId
              << " " << node.conjForm << " " << node.conjFormId
              << " " << node.feat << " " << node.featflag << "\t" << node.redirect << "\n";
}
std::cout << std::endl;
```
```
この::この この 指示詞 7 連体詞形態指示詞 2 * 0 * 0 * 0	
アボガド::アボガド アボガド 名詞 6 普通名詞 1 * 0 * 0 自動獲得:Wikipedia Wikipediaリダイレクト:アボカド 0	アボカド
に::に に 助詞 9 格助詞 1 * 0 * 0 * 0	
は::は は 助詞 9 副助詞 2 * 0 * 0 * 0	
魅力::みりょく 魅力 名詞 6 普通名詞 1 * 0 * 0 代表表記: カテゴリ:抽象物 0	
が::が が 助詞 9 格助詞 1 * 0 * 0 * 0	
たっぷり::たっぷり たっぷりだ 形容詞 3 * 0 ナノ形容詞 22 語幹 1 代表表記: 0	
と::と と 助詞 9 格助詞 1 * 0 * 0 * 0	
詰まって::つまって 詰まる 動詞 2 * 0 子音動詞ラ行 10 タ系連用テ形 14 代表表記: ドメイン:料理・食事 自他動詞:他:詰める/つめる 0	
いる::いる いる 接尾辞 14 動詞性接尾辞 7 母音動詞 1 基本形 2 代表表記: 0	
。::。 。 特殊 1 句点 1 * 0 * 0 * 0	
```
-----

### <a name="wakati">std::string Jumanpp::wakati(std::string text)

get the wakati.

```c++
std::cout << jpp.wakati("魅力がたっぷりと詰まっている。") << std::endl;
```
```
魅力 が たっぷり と 詰まって いる 。
```
-----


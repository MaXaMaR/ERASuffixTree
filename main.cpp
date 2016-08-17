// Implemented by Maxim Tishkov
//
// Created using ERA paper
// http://www.vldb.org/pvldb/vol5/p049_essammansour_vldb2012.pdf
// Essam Mansour, Amin Allam, Spiros Skiadopoulos, Panos Kalnis
//

#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include "SuffixTree.hpp"
#include "utils/MemoryLeakDatabase.hpp"
#include "utils/StringVector.hpp"

int main() {

    for (uint64 i = 0; i < 1000000; i++) {
//        std::string str = "ewrqwewqeqwerqweerrqwwewrewewrweqweerqwr"
//                "eqwweeerqewerqweeqweqrweqwerqweqeweqwreqweeqeeqwqqweerqwreqeweqrweqw"
//                "erqwewrqwewqeqwerqweerrqwwewrewewrweqweerqwreqwweeerqewerqweeqweqrweq"
//                "werqweqeweqwreqweeqeeqwqqweerqwreqeweqrweqwerqwewrqwewqeqwerqweerrqwwe"
//                "wrewewrweqweerqwreqwweeerqewerqweeqweqrweqwerqweqeweqwreqweeqeeqwqqwee"
//                "rqwreqeweqrweqwerqwewrqwewqeqwerqweerrqwwewrewewrweqweerqwreqwweeerqewe"
//                "rqweeqweqrweqwerqweqeweqwreqweeqeeqwqqweerqwreqeweqrweqwerqwewrqwewqeqwe"
//                "rqweerrqwwewrewewrweqweerqwreqwweeerqewerqweeqweqrweqwerqweqeweqwreqweeqe"
//                "eqwqqweerqwreqeweqrweqwerqwewrqwewqeqwerqweerrqwwewrewewrweqweerqwreqwweee"
//                "rqewerqweeqweqrweqwerqweqeweqwreqweeqeeqwqqweerqwreqeweqrweqwerqw";

        std::string str = "sdfasdfadadgadfgaergdlkfgdslkgjdfgljdfs;kgldfg"
                "aefjseghdfghdszfgasfhawgerawevwetvwertvert"
                "weafhasifashfiuawehfuyszfgsudyifbfdfhbdfsjhgjhkguyifytfvytfvtuyrvrtudfytbd"
                "hyfttctryxytdcturdcytrfuytfvhuyguigouymsfnfkjhsdlfkhaefhaerhgsdlfjg"
                "fjaefuehfoiuwefhsizofhfdgjdfhgkszjdfhgfsdkjgbseiutgersuifbdfjkvdfxgbdfgsdzf"
                "dsfaewfhawuifhzsdfhzsofuzebfhzawfalkfdsnfkajsldfsadjfasd"
                "afsdfjaweioufhweirwearweirewrwerwewrwerwerewrwewr"
                "rwearwerwerwerewewrewrewrwerewrewrwerwersadfasdnfsdjkfsdaf"
                "asdfsadfjasifhaweiufhasfgasuiyfegwarwaerawerewarwer"
                "werewrewewrweretertertwertrewtwertewtwyeetrouierwtwer"
                "twerterwtuiwerterwuterwutewryterwytrweterwt"
                "ewrterwterwterwtrewtwtrweterwtertertreterterttretretrere"
                "tertreterreterterererytuertuyeritwertywereywuruywtwe"
                "rwertewuyrtwerewryewureuwtrutewurwetrtuweutyrwe"
                "werwerewtrewuwetewuyrtyewtruewuytrtuewyutryeuyewutrwe"
                "ewrweryewrtwertweturewyrutweyruyewtyrweurtweur"
                "werwertweurtyewtyrtuwtrewreuytweutruyewuyweyutryutwetr"
                "ewrwertwetrwetruweyrtwetrtyweyuruytwtyetwetewrrwerwerew"
                "rweretewrterwterwtwertwerterwterewrwerwerwer"
                "ewtwertewrtrewterwterwtwertefusebfzskefbzskefhjsdbfkzhjsdfd"
                "ertewrterwtewrytierwtyweurtweurewrwertweurwearwerwearwaerwaerewartertertert"
                "wertweruywteurwetuyirqweuyryutqwetirqwuertqweutrtqweutruqtwiertyiqwtuert"
                "rqwerwertewuqrtqwyuertquweyrtqweurtweqiruqwtertuqwetrtuyqweyrttwqyeurtyeuwtrquywe"
                "wqerqwerwertwqeuruwteqrtuwquetrtweetwrutqywretwqutrytweuytruytweuytruywertew"
                "rwertweryweurtweuyrtuetuewtwretuyewyturtywertwetyrytweryutewtyrtyweytrewtyryt"
                "wrweirewtrytwetrewytuweruyteutyrweytrtuywertuyewtwetettrutwetrtywetrszfftyivuygugb"
                "vgfuytfybiuuybitot78ttiytyutityutuyyututyuytaertae tesrts dfg sdfg sadf aerf sdzg f";
//        std::string str = "TGGTGGTGGTGCGGTGATGGTGC";
        auto dataSource = std::make_shared<StringDataSource>(str);
        // items per virtual tree / per thread & items per read
        auto config = std::make_shared<SuffixTreeConfig>(100, 100);
        auto builder = SuffixTreeBuilder(dataSource, config);
        auto res = builder.build();

        std::cout << "Found leaves:" << std::endl;
        for (auto it = res->getRootNode()->leavesBegin(); it != res->getRootNode()->leavesEnd(); it++) {
            std::cout << it->getPath() << std::endl;
        }

        std::cout << "Follow path res: " << std::endl;

        // Append $ to get leaf
        std::string findingStr = "urtweurewrwertweurw";
        auto result = res->getRootNode()->followPath(StringVector(findingStr).getVector());

        if (result != nullptr) {
            std::cout << result->getPath() << std::endl;
            std::cout << "Is Leaf: " << result->isLeaf() << std::endl;
        } else {
            std::cout << "Not Found" << std::endl;
        }

        // Edges sometimes start with the same prefix
        // So that check is disabled
        res->getInfo()->check();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    MemoryLeakDatabase::dump();

    return 0;
}

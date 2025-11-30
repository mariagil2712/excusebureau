//Código de María Gil e Isabella Ramírez

#include <iostream>

#include <list>
#include <vector>
#include <map>

using namespace std;
typedef int Element;

class CompactChainList {
private:
    list<pair<Element, int>> l;

public:
    CompactChainList(vector<Element> &secuencia); //2
    int getConsecutiveOcurrences(vector<Element> &subsecuencia); //11
    //Print
    void printPairs();

};

void CompactChainList::printPairs() { //print
    int n = l.size();
    int i = 0;
    cout << "[";
    for (auto& pareja : l) {
        if( i < n - 1)
            cout << "{" << pareja.first << ", " << pareja.second << "},";
        else
            cout << "{" << pareja.first << ", " << pareja.second << "}";
        ++i;
    }
    cout << "]" << endl;
}

CompactChainList::CompactChainList(vector<Element> &secuencia) {
    int i = 1;
    Element valor = secuencia[0];
    int ocurrencias = 1;

    while (i < secuencia.size()) {
        if (secuencia[i] == valor) {
            ocurrencias = ocurrencias + 1;
        }
        else {
            l.push_back({valor, ocurrencias});
            valor = secuencia[i];
            ocurrencias = 1;
        }
        i = i + 1;
    }

    l.push_back({valor, ocurrencias});
}

int CompactChainList::getConsecutiveOcurrences(vector<Element> &subsecuencia) {
    int ocurrences = 0;
    CompactChainList subS(subsecuencia);
    //Caso donde la subsecuencia solo tiene un elemento
    if(subS.l.size() == 1) {
        list<pair<Element, int>>::iterator itsub = subS.l.begin();
        for(list<pair<Element, int>>::iterator itlist = l.begin(); itlist != l.end(); ++itlist) {
            if((*itlist).first == (*itsub).first) {
                //Cuenta las ocurrencias cuando las repeticiones de una pareja en la secuencia son mayores a las de la subsecuencia y la subsecuencia tiene un solo elemento
                ocurrences += (itlist->second - itsub->second) + 1;
            }
        }
    } else {
        list<pair<Element, int>>::iterator itlist = l.begin();
        while(itlist != l.end()) {
            bool match = true;
            list<pair<Element, int>>::iterator itsub = subS.l.begin();
            list<pair<Element, int>>::iterator itlistcopy = itlist;
            while(itsub != subS.l.end() && match == true && itlistcopy != l.end()) {
                //El elemento debe coincidir
                if(itlistcopy->first != itsub->first) {
                    match = false;
                }
                // El itlist.second >= que el itsub.second
                else if(itsub->second > itlistcopy->second) {
                    match = false;
                }
                //las parejas en la mitad deben ser excatamente iguales
                else if(itsub != subS.l.begin() && itsub != --subS.l.end()) {
                    if(itlistcopy->second != itsub->second) {
                        match = false;
                    }
                }
                ++itsub;
                ++itlistcopy;
            }
            if(match == true && itsub == subS.l.end())
                ocurrences += 1;

            ++itlist;
        }
    }
    return ocurrences;
}

int main() {


    return 0;
}


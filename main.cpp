//Código de María Gil e Isabella Ramírez

#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <string>

using namespace std;
typedef char Element;

class CompactChainList {
private:
    list<pair<Element, int>> l;

public:
    CompactChainList() {}
    CompactChainList(vector<Element> &secuencia) {
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

    int getConsecutiveOcurrences(vector<Element> &subsecuencia) {
        int ocurrences = 0;
        CompactChainList subS(subsecuencia);
        //Caso donde la subsecuencia solo tiene un elemento
        if(subS.l.size() == 1) {
            list<pair<Element, int>>::iterator itsub = subS.l.begin();
            for(list<pair<Element, int>>::iterator itlist = l.begin(); itlist != l.end(); ++itlist) {
                if(itlist->first == itsub->first && itlist->second >= itsub->second) {
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

    void printPairs() {
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

    list<Element> expand() {
    list<Element> ans;
    for(list<pair<Element, int>>::iterator it = l.begin(); it != l.end(); ++it) {
        Element ele = it->first;
        int rep = it->second;
        for(int i = 0; i < rep; ++i){
            ans.push_back(ele);
        }
    }
    return ans;
}

};

string descomprimirCCL(CompactChainList &ccl) {
    string reporte;
    list<Element> lista = ccl.expand();
    for(list<Element>::iterator it = lista.begin(); it != lista.end(); ++it) {
        reporte += (*it);
    }
    return reporte;
}


int main() {
    int K;
    int E;
    while (cin >> K >> E) {
        cin.ignore();  // ← ignora el \n después de leer E

        vector<CompactChainList> concepts;
        vector<CompactChainList> reports;

        // convertir los conceptos en ccls y guardarlos en concepts
        int i = 0;
        while (i < K) {
            string con;
            vector<char> temp;
            cin >> con;
            size_t j = 0;
            while (j < con.size()) {
                temp.push_back(con[j]);
                j = j + 1;
            }
            concepts.push_back(CompactChainList(temp));
            i = i + 1;
        }

        cin.ignore();

        // lo mismo para reports
        int m = 0;
        while (m < E) {
            string rep;
            vector<char> temp;
            getline(cin, rep);
            size_t t = 0;
            while (t < rep.size()) {
                temp.push_back(rep[t]);
                t = t + 1;
            }
            reports.push_back(CompactChainList(temp));
            m = m + 1;
        }

        // impresion (LO PUEDES BORRAR)
        int x = 0;
        while (x < concepts.size()) {
            concepts[x].printPairs();
            cout << endl;
            string concepto = descomprimirCCL(concepts[x]);
            cout << concepto << endl;
            x = x + 1;
        }

        // impresion (LO PUEDES BORRAR)
        int y = 0;
        while (y < reports.size()) {
            reports[y].printPairs();
            cout << endl;
            string reporte = descomprimirCCL(reports[y]);
            cout << reporte << endl;
            y = y + 1;
        }
    }

    return 0;
}


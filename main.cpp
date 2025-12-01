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
                if(itlist->first == itsub->first && itlist->second >= itsub ->second) {
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


int main() {
    int K;
    int E;
    while (cin >> K >> E) {
        cin.ignore();

        vector<vector<char>> concepts;
        vector<string> reports;
        vector<pair<int, CompactChainList>> reportsccl; //pares (ocurrencias, ccl)

        // convertir los conceptos en vectores de char y guardarlos en concepts
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
            concepts.push_back(temp);
            i = i + 1;
        }

        cin.ignore();

        // convertir los reportes en vectores y guardarlos en reportesccl Y tmb en reportes donde estarán normales como string
        int m = 0;
        while (m < E) {
            string rep;
            vector<char> temp;
            getline(cin, rep);
            reports.push_back(rep); //aqui lo guardo normal
            size_t t = 0;
            while (t < rep.size()) {
                char temp2 = rep[t];
                if (temp2 >= 'A' && temp2 <= 'Z') { //si es mayuscula
                    temp2 = temp2 + 32;
                }
                temp.push_back(temp2);
                t = t + 1;
            }
            reportsccl.push_back({0, CompactChainList(temp)});
            m = m + 1;
        }

        int h = 0;
        while (h < reportsccl.size()) { //por cada report en formato ccl
            int g = 0;
            while (g < concepts.size()) { //busco cada concepto
                int ocurrencias = reportsccl[h].second.getConsecutiveOcurrences(concepts[g]); //ocurrencias del primer concepto
                reportsccl[h].first = reportsccl[h].first + ocurrencias; //las sumo
                g = g + 1; //avanzo de concepto
            }
            h = h + 1; //avanzo de ccl
        }

        int greatestOcurrencia = 0;
        int p = 0;
        while (p < reportsccl.size()) { //buscaré cual fue el mayor numero de conceptos ocurridos en un mismo reporte
            if (reportsccl[p].first > greatestOcurrencia) {
                greatestOcurrencia = reportsccl[p].first;
            }
            p = p + 1;
        }


        //ahora voy a recorrer reportsccl buscando los indices de aquellas que tienen greatestOcurrencia y las imprimo
        int u = 0;
        while (u < reportsccl.size()) {
            if (reportsccl[u].first == greatestOcurrencia) {
                cout << reports[u] << endl;
            }
            u = u + 1;
        }

        cout << endl;


    }

    return 0;
}


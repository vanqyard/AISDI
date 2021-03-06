/**
@file asd.cc

Plik do modyfikacji w ramach cwiczenia z AISDI.
Zawiera niekompletne implementacje metod klasy ListMap,
oraz mape podobna koncepcyjnie do tej z cwicznia 1 (SmallMap)
zaimplementowana w jescze bardziej szczatkowy sposob.
Jest tez prosta funkcja testujaca (void test()), ktora
jest wolana w funkcji main. Mozna w niej zaimplementowac
wlasne testy.
NALEZY ZMODYFIKOWAC I UZUPELNIC CIALA METOD KLASY LISTMAP.

@author
Pawel Cichocki, Michal Nowacki

@date
last revision
- 2006.01.06 Michal Nowacki: wersja polska
- 2005.11.17 Michal Nowacki: constructor
- 2005.11.04 Pawel Cichocki: copied comments from the header
- 2005.11.03 Pawel Cichocki: const_iterator done properly now
- 2005.10.27 Pawel Cichocki: cosmetic changes
- 2005.10.26 Michal Nowacki: removed some method bodies
- 2005.10.25 Pawel Cichocki: wrote it

COPYRIGHT:
Copyright (c) 2005 Instytut Informatyki, Politechnika Warszawska
ALL RIGHTS RESERVED
*******************************************************************************/

#include <assert.h>
#include <algorithm>

#include <iostream>

#include "ListMap.h"

//////////////////////////////////////////////////////////////////////////////
// ListMap and ListMap::iterator methods
//////////////////////////////////////////////////////////////////////////////

ListMap::ListMap()
{
   first = new Node(std::make_pair(0," "));
   first->next = first;
   first->prev = first;
};

ListMap::ListMap( const ListMap& m )
{
	///@todo Zaimplementować metode
	//first = NULL;
	//for(const_iterator it = m.begin(); it != m.end(); ++it)
	//	m.insert();
};

ListMap::~ListMap()
{
	clear();
};

// Wstawienie elementu do mapy.
// @returns Para, której komponent bool jest równy true gdy wstawienie zostało
//          dokonane, równy false gdy element identyfikowany przez klucz
//          już istniał w mapie. Iterator ustawiony jest na ten wstawiony
//          lub istniejący już w mapie element.
std::pair<ListMap::iterator, bool> ListMap::insert(const std::pair<Key, Val>& entry)
{
	for(iterator i=begin(); i!=end(); ++i)
	{
		if(i->first==entry.first)
			return std::make_pair(i, (bool)false);
	}
	
	return std::make_pair(unsafe_insert(entry), true);
}

// Wstawienie elementu do mapy.
// Matoda zakłada, że w mapie nie wystêpuje element identyfikowany przez key
ListMap::iterator ListMap::unsafe_insert(const std::pair<Key, Val>& entry)
{
	Node* new_node = new Node(entry);
	first->next->prev = new_node;
	new_node->next = first->next;
	new_node->prev = first;
	first->next = new_node;
	
	return iterator(new_node);	
}

// Zwraca iterator addresujący element w mapie dla którego klucz jest równy
// szukanemu kluczowi lub element za ostatnim gdy szukanego klucza brak w mapie.
ListMap::iterator ListMap::find(const Key& k)
{
   	for(iterator i=begin(); i!=end(); ++i)
	{
		if(i->first==k)
			return iterator(i);
	}
	
	return end();
}

ListMap::const_iterator ListMap::find(const Key& k) const
{
	for(const_iterator i=begin(); i!=end(); ++i)
	{
		if(i->first==k)
			return const_iterator(i);
	}
	
	return end();
}

// Udostêpnia wartoæ powiązaną z kluczem key. Wstawia element do mapy jeli
// nie istniał.
// @returns Referencje do wartoci powiązanej z kluczem.
ListMap::Val& ListMap::operator[](const Key& k)
{
   ///@todo Zaimplementowaæ metode
   //assert(0);
	iterator i = insert(std::make_pair(k," ")).first;
	return i->second;
}

// Sprawdzenie czy mapa jest pusta.
bool ListMap::empty( ) const
{
   return first->next==first;
}

// Zwraca iloæ elementów w mapie.
ListMap::size_type ListMap::size( ) const
{
   ///@todo Zaimplementowaæ metode
   assert(0);
   return 0;
}

// Zwraza iloæ elementów skojarzonych z kluczem key.
ListMap::size_type ListMap::count(const Key& _Key) const
{
   ///@todo Zaimplementowaæ metode
   return 1;  // this is not a multimap
}

// Usuwa element z mapy.
// @returns iterator adresujący pierwszy element za usuwanym.
ListMap::iterator ListMap::erase(ListMap::iterator i)
{
	///@todo Zaimplementowaæ metode
	//assert(0);
	i.node->prev->next = i.node->next;
	i.node->next->prev = i.node->prev;
	delete i.node;
	return end();
}

// Usuwa zakres elementów z mapy.
// Zakres jest zdefiniowany poprzez iteratory first i last
// first jest okrela pierwszy element do usuniêcia, a last okrela element
// po ostatnim usuniêtym elemencie.
// @returns iterator adresujący pierwszy element za usuwanym.
ListMap::iterator ListMap::erase(ListMap::iterator f, ListMap::iterator l)
{
	///@todo Zaimplementowaæ metode
	//assert(0);
	//trzeba sprawdzic czy f < l
	iterator start = find(f->first);
	iterator finish = find(l->first);
	if(start == end()) return end();
	if(finish == end()) return end();
	
	if(start->first < finish->first) {
		std::cout << "Valid erase" << std::endl;
		iterator it = f;
		iterator tmp;
		
		while(it!=l) {
			tmp = it;
			it++;
			std::cout << "Erasing element: " << tmp->first << " " << tmp->second << std::endl;
			erase(tmp);
		}
		return it;
	} else {
		std::cout << "Bad erase" << std::endl;
		return end();
	}
}

// Usuwa element z mapy.
// @returns Ilość usuniętych elementów.
//          (nie jest to multimapa, więc może być to wartość 1 lub 0 )
ListMap::size_type ListMap::erase(const Key& key)
{
	iterator i = find(key);
	if(i != end()) {
		erase(i);
		return 1;
	} else
		return 0;
}

// Usuniêcie wszystkich elementów z mapy.
void ListMap::clear( )
{
   ///@todo Zaimplementowaæ metode
   //assert(0);
   erase(begin(), end());
}

// Porównanie strukturalne map.
// Czy reprezentacja danych jest identyczna.
// Zwraca true jeli wewnêtrzne struktury map są identyczne.
bool ListMap::struct_eq(const ListMap& another) const
{
   ///@todo Zaimplementowaæ metode
   assert(0);
   return false;
}

// Porównanie informacyjne map.
// Czy informacje trzymane w mapach są identyczne.
// Zwraca true jeli mapy zwierają takie same pary klucz-wartoæ.
bool ListMap::info_eq(const ListMap& another) const
{
   ///@todo Zaimplementowaæ metode
   assert(0);
   return false;
}

// preinkrementacja
ListMap::const_iterator& ListMap::const_iterator::operator++()
{
	node=node->next;
	return *this;
}

// postinkrementacja
ListMap::const_iterator ListMap::const_iterator::operator++(int)
{
	const_iterator akt=*this;
	node=node->next;
	return akt;
}

// preinkrementacja
ListMap::const_iterator& ListMap::const_iterator::operator--()
{
	node=node->prev;
	return *this;
}

// postinkrementacja
ListMap::const_iterator ListMap::const_iterator::operator--(int)
{
	const_iterator akt=*this;
	node=node->prev;
	return akt;
}

/// Zwraca iterator addresujący pierwszy element w mapie.
ListMap::iterator ListMap::begin()
{
	return iterator(first->next);
}

/// Zwraca iterator addresujący pierwszy element w mapie.
ListMap::const_iterator ListMap::begin() const
{
   return iterator(first->next);
}

/// Zwraca iterator addresujący element za ostatnim w mapie.
ListMap::iterator ListMap::end()
{
   return iterator(first);
}

/// Zwraca iterator addresujący element za ostatnim w mapie.
ListMap::const_iterator ListMap::end() const
{
   return iterator(first);
}

//////////////////////////////////////////////////////////////////////////////
// SmallMap
//////////////////////////////////////////////////////////////////////////////

/// Przykład map'y z implementacją podobną do std::map.
/// To jest jedynie przykład!!!
/// Normalnie implementacja powinna opieraæ siê o drzewo lub tablicê haszującą.
template <class Key, class Val>
class SmallMap
{
   std::pair<Key, Val> tab[2];
   int isOcupied[2];
public:

   SmallMap()
   {
      for(unsigned i=0; i<2; ++i)
      {
         isOcupied[i]=0;
      }
   }

   typedef std::pair<Key, Val>* iterator;   ///< Każdy wskaźnik jest też iteratorem.

   iterator begin() { return tab; }
   iterator end() { return tab+2; }

   Val& operator[](const Key& k)
   {
      static Val val;
      for(unsigned i=0; i<2; ++i)
      {
         if(isOcupied[i]&&tab[i].first==k)
            return tab[i].second;
      }
      // create
      for(unsigned i=0; i<2; ++i)
      {
         if(!isOcupied[i])
         {
            tab[i].first=k;
            isOcupied[i]=1;
            return tab[i].second;
         }
      }
      //std::cout<<"Out of space! You should not put more than two Key-Value pairs into the SmallMap.\n";
      std::cerr<<"Out of space! You should not put more than two Key-Value pairs into the SmallMap.\n";
      //assert(0);
      return val;   // Mało sensowne, ale to jest tylko przykłąd
   }
};


//////////////////////////////////////////////////////////////////////////////
// Testy
//////////////////////////////////////////////////////////////////////////////

/// Funckcja pomocnicza do wypisania elementów.
void print(const std::pair<int, std::string>& p)
{
   std::cout<<p.first<<", "<<p.second<<std::endl;
}

#include <map>

// A typedef used by the test.
//typedef std::map<int, std::string> TEST_MAP;
//typedef SmallMap<int, std::string> TEST_MAP;
typedef ListMap TEST_MAP;

/// Testy użytkownika
void test()
{
	TEST_MAP m;

	std::cout << "Testy uzytkownika" << std::endl;
	
	/*
	m[2] = "Merry";
	m[4] = "Jane";
	m[8] = "Korwin";
	m[4] = "Magdalena";

	for_each(m.begin(), m.end(), print );
	//system("PAUSE");
	*/
	
	//std::pair<ListMap::iterator, bool> n = m.insert(std::pair<int,std::string>(1, "SomeWord1"));
	//std::cout << "if inserted:" << n.second << std::endl;
	//print(*(n.first));
	
	std::cout << "Testing insert" << std::endl;
	m.insert(std::pair<int,std::string>(1, "SomeWord1"));	
	m.insert(std::pair<int,std::string>(2, "SomeWord2"));
	m.insert(std::pair<int,std::string>(3, "SomeWord3"));
	m.insert(std::pair<int,std::string>(4, "SomeWord4"));
	m.insert(std::pair<int,std::string>(5, "SomeWord5"));	
	m.insert(std::pair<int,std::string>(1, "SomeWord4"));
	for_each(m.begin(), m.end(), print );
	std::cout << "#################" << std::endl << std::endl;
	
	std::cout << "Testing find" << std::endl;	
	std::cout << "Trying to find 3" << std::endl;
	ListMap::iterator it = m.find(3);
	print(*it);
	std::cout << "#################" << std::endl << std::endl;

	std::cout << "Testing erase" << std::endl; 
	bool status = m.erase(3);
	std::cout << "Erasing 3, status: " << status << std::endl;
	for_each(m.begin(), m.end(), print );
	std::cout << "#################" << std::endl << std::endl;
	
	std::cout << "Testing operator[]" << std::endl; 
	m[100] = "testing";
	for_each(m.begin(), m.end(), print );
	std::cout << "#################" << std::endl << std::endl;

	std::cout << "Testing erase by range" << std::endl; 
	m.erase(m.find(2), m.find(5));
	for_each(m.begin(), m.end(), print );
	std::cout << "#################" << std::endl << std::endl;

	/*
	std::cout << "Testing clear" << std::endl; 
	m.clear();
	for_each(m.begin(), m.end(), print );
	std::cout << "#################" << std::endl << std::endl;
	*/
}

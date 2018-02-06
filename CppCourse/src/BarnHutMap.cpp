#include "BarnHutMap.h"
#include <algorithm>

namespace caveofprogramming
{

    BarnHutMap::BarnHutMap()
    {
        // Initalize the entries array
        m_entries = new std::vector<MapEntry> *[BarnHutMap::ARRAY_LEN];
        for ( int i = 0; i < BarnHutMap::ARRAY_LEN; i++ )
        {
            m_entries[i] = new std::vector<MapEntry>;
        }
    }

    BarnHutMap::~BarnHutMap()
    {
    }

    void BarnHutMap::clear()
    {
        /*
        m_entries = new std::vector<MapEntry> *[BarnHutMap::ARRAY_LEN];
        for ( int i = 0; i < BarnHutMap::ARRAY_LEN; i++ )
        {
            m_entries[i] = new std::vector<MapEntry>;
        }
        */
    }

    void BarnHutMap::add( VerletPoint *key, BarnHutMulti *value )
    {
        int hashindex = key->hash() % BarnHutMap::ARRAY_LEN;

        MapEntry newEntry;
        newEntry.point = key;
        newEntry.value = value;

        MapEntry remove;
        /*
        for ( int i = 0; i < m_entries[hashindex]->size(); i++ )
        {
            if ( m_entries[hashindex]->at( i ).point == key )
            {
                // The key is already in the list so we remove it for the update
                remove = m_entries[hashindex]->at( i );
                break;
            }
        }

        if ( remove.point != nullptr )
        {
            m_entries[hashindex]->erase( std::remove_if( m_entries[hashindex]->begin(),
                                                         m_entries[hashindex]->end(),
                                                         [&]( MapEntry const &entry ) {
                                                             return entry.point == remove.point;
                                                         } ),
                                         m_entries[hashindex]->end() );
        }*/

        // m_entries[hashindex]->push_back( newEntry );
    }

    void BarnHutMap::remove( VerletPoint *key )
    {
        // Remove from vector
    }

    BarnHutMulti *BarnHutMap::get( VerletPoint *key )
    {
        int hashindex = key->hash() % BarnHutMap::ARRAY_LEN;

        for ( int i = 0; i < m_entries[hashindex]->size(); i++ )
        {
            if ( m_entries[hashindex]->at( i ).point == key )
                return m_entries[hashindex]->at( i ).value;
        }
    }
}

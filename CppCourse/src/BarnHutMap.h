#ifndef BARNHUTMAP_H
#define BARNHUTMAP_H

namespace caveofprogramming
{
    class BarnHutMap
    {
      private:
        BarnHutMulti **m_mapList;

      public:
        BarnhutMap( int max );
        virtual ~BarnHutMap();

        void add( VerletPoint *key, BarnHutMulti *item );
        void remove( VerletPoint *key );
        BarnHutMulti **get( VerletPoint *key );
    }
}

#endif /* BARNHUTMAP_H */

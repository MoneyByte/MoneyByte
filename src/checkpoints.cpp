// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2019 The MoneyByte Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "txdb.h"
#include "main.h"
#include "uint256.h"


static const int nCheckpointSpan = 5000;

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints = boost::assign::map_list_of
            (0, uint256("0x000015f3db3555810163ed676759c73e21be211ed3dcfda4454c29796abc2e37"))
            (1000, uint256("0x32aa9f844abf3cfc03e104148b25369df194f88ba1e88a83c521244fce8fab56"))
            (10000, uint256("0x45ff9dd41d4b04dfc7ede906ba20ae6d949c9984efc62a2cf10a29d07b14c338"))
            (50000, uint256("0xe116509063f7a4845382dbd63ec3a97f7f325c0e4de95fa067090a78dd37411f"))
            (75000, uint256("0x061e54fe225c6f50a14e264db2d19f458f671303a9c91f323fabb2891618cf95"))
            (100000, uint256("0x35ca415856fc6825475468df2a0688dabcabdfb0d9a668ae28d38db432756024"))
            (125000, uint256("0x3a4198dc0018d82d7692142fce55dd07211bab3a20bb58097e7d4e0564d709cc"))
            (150000, uint256("0x322305af4014b901f71cdc96af45fd1bc0aa4f9e413c2a6008b69fffed7a37cf"))
            (175000, uint256("0xf42f35a3b3093683feaab596e049138d0f7299a6e02da516efc67969a817705d"))
            (200000, uint256("0x3dba2dd2e842b4e1425261bac7b59099eec752cc4bfca8d36d799a2afc7c301e"))
            (225000, uint256("0x7e1dc61dfa11aa0e515db6ed1ca4ab0c8e5c26fb55f761f6f2b6b006ddbb2798"))
            (250000, uint256("0xdbb4acfe6faf213863d6f7760bd5ed647f34130a51964b3a4653e0972279216f"))
            (275000, uint256("0x0ddcd17cabb48a8ec26de8a7b33a564141c188d41c61004a358d48c5f0a7533a"))
    ;

    // TestNet has no checkpoints
    static MapCheckpoints mapCheckpointsTestnet = boost::assign::map_list_of
            (0, uint256(0x001))
    ;

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        if (checkpoints.empty())
            return 0;
        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }

    // Automatically select a suitable sync-checkpoint
    const CBlockIndex* AutoSelectSyncCheckpoint()
    {
        const CBlockIndex *pindex = pindexBest;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
            pindex = pindex->pprev;
        return pindex;
    }

    // Check against synchronized checkpoint
    bool CheckSync(int nHeight)
    {
        const CBlockIndex* pindexSync = AutoSelectSyncCheckpoint();
        if (nHeight <= pindexSync->nHeight){
            return false;
        }
        return true;
    }
}

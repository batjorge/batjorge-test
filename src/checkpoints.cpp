// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "txdb.h"
#include "main.h"
#include "uint256.h"


static const int nCheckpointSpan = 500;

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
    //
    static MapCheckpoints mapCheckpoints = 
        boost::assign::map_list_of
	(       0, uint256("0x00000289de5d7381e8498bdff3dc61bf0587f7af174fc4dfffeab65eb663aa7d") )
	(       1, uint256("0x5ed22dbadb1575884cd1b9fbd30662b7c673f414c74039db063a4b31c4515ee3") )
	(      11, uint256("0xbfeeb39f8d2643666acd55fc9b497963e9ecbaf7c4937ab397df55018fad7109") )
	(      33, uint256("0xdfd85e4ea767e38a797ac620349056cf218f70bc4b4a55d838a4c85cd450f94d") )
	(     333, uint256("0xc843e2ccfbf2aade448e8e07e9be7b4aa1e712bf922b5a660f34a6c43f1706b5") )
	(    1337, uint256("0xd6896cfaa031a4fb941482c7ee3dbb31cf037257f7ff97dd0bfecc11238e4661") ) 
	(    1677, uint256("0xf8b652ec1736ae10289af3aabaf35bdeb65bfc7f3143cf9869501b370c083f4c") )
	(    8192, uint256("0xf3e32c8d9c9e01dfc052c22e59d12d8d4f531b9f0bd9dd60d3dabc28f080cb7e") )
	(   10012, uint256("0xd272a7c55b4fb511c21e17b6b62aa32786e3b3b1ad05d084ffaaef1db9cdd39b") )
    ;

    // TestNet has no checkpoints
    static MapCheckpoints mapCheckpointsTestnet;

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

        if (nHeight <= pindexSync->nHeight)
            return false;
        return true;
    }
}

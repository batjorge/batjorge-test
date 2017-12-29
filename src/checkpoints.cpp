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
	(       0, uint256("0x00000e0f29299cb61417ca4433a11ff61b057113338f30b5f89ff9f88c3d8cba") )
	(       1, uint256("0xb7efed5ad540199084fb5efdd9951d3599960020b79c72e90bf663ad20d9df9d") )
	(      10, uint256("0xe1952834d7da49b9e79efb2deb9a8b7dde2299bf04b07530e222a3f2f61fcd78") )
	(      20, uint256("0xea4bc2729a5315edb39f0f16fb64470258fcc7197bdecacfb8a431befc667fa6") )
	(      30, uint256("0xe88177619c475ac32ef236cc21eb847a3f938f50048aff89eb06001f3fcb6a8c") )
	(      40, uint256("0x842ec44ff01b657a9deb9989bb2d5bc888521fd5d8e45838cd97db6e9f3fe3e1") )
	(      50, uint256("0x79875efd656366fd3404b737a943244b7f8c14eb698523992f39b0afbe14c66f") )
	(      60, uint256("0x6278f77249031d9ce7d97e9cef2d2140f615f1ccebc733301b8e5289e660c297") )
	(      70, uint256("0x05ceb6795594f5eab528393643c733df027f915539a5d5e2a82a33ebe92c4dce") )
	(      80, uint256("0xaca8587e914cf096d6fb7fab4da57be1382c46232fb32299ba5121189625f80e") )
	(      90, uint256("0xd2558f8e3d62eda969bf85cd0c2bb026fd765de9153b48393b081ee25a5e35c9") )
	(     100, uint256("0xf5cb38187e54fc232cf0d556f5afe87d0ffb2332962d40dd5c44fc350a617ce9") )
	(     123, uint256("0xedc3ed9f22f7529fdf5291e22c8f8e8ffa1b643d91e73646f6a74bd98fb7a3f1") )
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

// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xb1;
        pchMessageStart[1] = 0x32;
        pchMessageStart[2] = 0xb2;
        pchMessageStart[3] = 0x64;
        vAlertPubKey = ParseHex("04a14f57c57ffcc3328fcda59999e33a77701306b91bcc8efaf9d82bf4c93be9bdb1f80e1a6aa26677a98b4cfe32e63815ce4053f30aacceb6d6b748fe8ce28cdd");
        nDefaultPort = 17654;
        nRPCPort = 17655;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
        //CBlock(hash=000001faef25dec4fbcf906e6242621df2c183bf232f263d0ba5b101911e4563, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=12630d16a97f24b287c8c2594dda5fb98c9e6c70fc61d44191931ea2aa08dc90, nTime=1393221600, nBits=1e0fffff, nNonce=164482, vtx=1, vchBlockSig=)
        //  Coinbase(hash=12630d16a9, nTime=1393221600, ver=1, vin.size=1, vout.size=1, nLockTime=0)
        //    CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a24323020466562203230313420426974636f696e2041544d7320636f6d6520746f20555341)
        //    CTxOut(empty)
        //  vMerkleTree: 12630d16a9
        const char* pszTimestamp = "CNN 09/Nov/2018 Michelle Obama: I'll never forgive Trump";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1541782800, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1541782800;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 3017471;

        hashGenesisBlock = genesis.GetHash();

	/*
	 *
	 *
	 */

	/*
	hashGenesisBlock = uint256("0x01");
	if (true && genesis.GetHash() != hashGenesisBlock)
	{
	printf("Searching for genesis block...\n");
	uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
	uint256 thash;

	while (true)
	{
	thash = genesis.GetHash();
	if (thash <= hashTarget)
	   break;
	if ((genesis.nNonce & 0xFFF) == 0)
	{
	   printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
	}
	++genesis.nNonce;
	if (genesis.nNonce == 0)
	{
	   printf("NONCE WRAPPED, incrementing time\n");
	   ++genesis.nTime;
	}
	}
	printf("genesis.nTime = %u \n", genesis.nTime);
	printf("genesis.nNonce = %u \n", genesis.nNonce);
	printf("genesis.nVersion = %u \n", genesis.nVersion);
	printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str()); //  first this, then comment this line out and uncomment the one under.
	printf("genesis.hashMerkleRoot = %s \n", genesis.hashMerkleRoot.ToString().c_str());   // find merkle root

       	}
	
	*/
	/* end genesis generation */

        assert(hashGenesisBlock == uint256("0x00000289de5d7381e8498bdff3dc61bf0587f7af174fc4dfffeab65eb663aa7d"));
        assert(genesis.hashMerkleRoot == uint256("0x7876eb03da3d82746951b93d3e2d821e5eff733fac95eb22dd29731bd7b8a7df"));

        vSeeds.push_back(CDNSSeedData("seed1.batjorge.com", "seed2.batjorge.com"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 43);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 105);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1, 153);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlockV1 = 10000;
	
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xcc;
        pchMessageStart[1] = 0xbb;
        pchMessageStart[2] = 0xdd;
        pchMessageStart[3] = 0xaa;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04f0a76f083364198910a9de263e57e56b113b6b4c8be57f1867cb4d48a51eb771f51cd7461205372d920a3b9ab82fc18e533579b671ba1c94c352feefeec3d9ec");
        nDefaultPort = 27654;
        nRPCPort = 27655;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 28120;
        hashGenesisBlock = genesis.GetHash();
	
	/*
	 *
	 */

	/*
	hashGenesisBlock = uint256("0x01");
	if (true && genesis.GetHash() != hashGenesisBlock)
	{
	printf("Searching for genesis block...\n");
	uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
	uint256 thash;

	while (true)
	{
	thash = genesis.GetHash();
	if (thash <= hashTarget)
	   break;
	if ((genesis.nNonce & 0xFFF) == 0)
	{
	   printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
	}
	++genesis.nNonce;
	if (genesis.nNonce == 0)
	{
	   printf("NONCE WRAPPED, incrementing time\n");
	   ++genesis.nTime;
	}
	}
	printf("genesis.nTime = %u \n", genesis.nTime);
	printf("genesis.nNonce = %u \n", genesis.nNonce);
	printf("genesis.nVersion = %u \n", genesis.nVersion);
	printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str()); //  first this, then comment this line out and uncomment the one under.
	printf("genesis.hashMerkleRoot = %s \n", genesis.hashMerkleRoot.ToString().c_str());   // find merkle root

       	}
	*/
	/* end genesis testnet */
	

        assert(hashGenesisBlock == uint256("0x000044829117ed26e6b3e8d2f7c7e69ac22ff207c0c8fb19b2f2ad898599b9ad"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1411111111;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 0;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 27656;
        strDataDir = "regtest";

	/*
	 *
	 */

	/*
	hashGenesisBlock = uint256("0x01");
	if (true && genesis.GetHash() != hashGenesisBlock)
	{
	printf("Searching for genesis block...\n");
	uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
	uint256 thash;

	while (true)
	{
	thash = genesis.GetHash();
	if (thash <= hashTarget)
	   break;
	if ((genesis.nNonce & 0xFFF) == 0)
	{
	   printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
	}
	++genesis.nNonce;
	if (genesis.nNonce == 0)
	{
	   printf("NONCE WRAPPED, incrementing time\n");
	   ++genesis.nTime;
	}
	}
	printf("genesis.nTime = %u \n", genesis.nTime);
	printf("genesis.nNonce = %u \n", genesis.nNonce);
	printf("genesis.nVersion = %u \n", genesis.nVersion);
	printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str()); //  first this, then comment this line out and uncomment the one under.
	printf("genesis.hashMerkleRoot = %s \n", genesis.hashMerkleRoot.ToString().c_str());   // find merkle root

       	}
	*/
	/* end genesis regtest */

        assert(hashGenesisBlock == uint256("0x5527c4dad68174bf268821cfcdd58f587d65013fa23bbc281f1223056e809c3c"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}

// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2018-2019 The Ignitioncoin Developers
// Copyright (c) 2019 The MoneyByte Developer - CircuitBreaker
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
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
	// It'll only connect to one or two seed nodes because once it connects,
	// it'll get a pile of addresses with newer timestamps.
	// Seed nodes are given a random 'last seen time' of between one and two
	// weeks ago.
	const int64_t nOneWeek = 7 * 24 * 60 * 60;
	for (unsigned int k = 0; k < count; ++k)
	{
		struct in_addr ip;
		unsigned int i = data[k], t;

		// -- convert to big endian
		t = (i & 0x000000ff) << 24u
			| (i & 0x0000ff00) << 8u
			| (i & 0x00ff0000) >> 8u
			| (i & 0xff000000) >> 24u;

		memcpy(&ip, &t, sizeof(ip));

		CAddress addr(CService(ip, port));
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
		pchMessageStart[0] = 0x21;
		pchMessageStart[1] = 0xf2;
		pchMessageStart[2] = 0x32;
		pchMessageStart[3] = 0xa5;
		vAlertPubKey = ParseHex("047d56dfe4da604d86552a456c8e40b8a56f979e73508851521d043b279301f32139ccc9f1475f3fc661b97138f0b49f65eff4deb025b23862075fadcd3538cc39");
		nDefaultPort = 7777;
		nRPCPort = 7778;
		bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
		/* The initial difficulty after switching to NeoScrypt (0.0625) */
		bnNeoScryptFirstTarget = CBigNum(~uint256(0) >> 28);

		// Build the genesis block. Note that the output of the genesis coinbase cannot
		// be spent as it did not originally exist in the database.

		const char* pszTimestamp = "On 9/9/2019 - 1568067357 - The MoneyByte Chain Officially Starts!";
		std::vector<CTxIn> vin;
		vin.resize(1);
		vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
		std::vector<CTxOut> vout;
		vout.resize(1);
		vout[0].SetEmpty();
		CTransaction txNew(1, 1426700641, vin, vout, 0);
		genesis.vtx.push_back(txNew);
		genesis.hashPrevBlock = 0;
		genesis.hashMerkleRoot = genesis.BuildMerkleTree();
		genesis.nVersion = 1;
		genesis.nTime = 1568067357;
		genesis.nBits = 520159231;
		genesis.nNonce = 21718;

		hashGenesisBlock = genesis.GetHash();

		assert(genesis.hashMerkleRoot == uint256("0xdb9398c8577ce37b62735aee0698dd3256255e2711847bba820fa491379a4580"));
		assert(hashGenesisBlock == uint256("0x000015f3db3555810163ed676759c73e21be211ed3dcfda4454c29796abc2e37"));


		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 51); // M
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 39); // G
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 138); // x
		base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1, 76); // X
		base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0x06)(0x2D).convert_to_container<std::vector<unsigned char> >();
		base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

		vSeeds.push_back(CDNSSeedData("46.101.203.85", "46.101.203.85"));
		vSeeds.push_back(CDNSSeedData("46.101.205.47", "46.101.205.47"));
		vSeeds.push_back(CDNSSeedData("207.154.225.242", "207.154.225.242"));
		vSeeds.push_back(CDNSSeedData("207.154.229.185", "207.154.229.185"));
		vSeeds.push_back(CDNSSeedData("139.59.208.102", "139.59.208.102"));
	//vSeeds.push_back(CDNSSeedData("", ""));

		convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

		nPoolMaxTransactions = 3;
		strDarksendPoolDummyAddress = "McUca9iVZ5eo8Ha79FfWz1ub5i36tJ2Gz7";
		nLastPOWBlock = nForkTwo + 200;
		nPOSStartBlock = 1;
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
		pchMessageStart[0] = 0x1d;
		pchMessageStart[1] = 0x7e;
		pchMessageStart[2] = 0xa6;
		pchMessageStart[3] = 0x2c;
		bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
		bnNeoScryptFirstTarget = CBigNum(~uint256(0) >> 20);
		vAlertPubKey = ParseHex("042a4acc6f2c09d425e45c73b11e8f5c2afefdab644689948dbe3e7efbd32bfe8a810ed0532359f42f6a15830137c28d10504056cb64539e5fea5f9ed1dc62aa2b");
		nDefaultPort = 33133;
		nRPCPort = 33155;
		strDataDir = "testnet";

		// Modify the testnet genesis block so the timestamp is valid for a later start.
		genesis.nBits = 520159231;
		genesis.nNonce = 47950;

	//assert(hashGenesisBlock == uint256("0x000088660811c8469e191c629657e36b6d339b9b76ce494cd9f957d59552bb3c"));

		vFixedSeeds.clear();
		vSeeds.clear();

		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 28);
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 38);
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 88);
		base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1, 98);
		base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
		base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

		convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

		nLastPOWBlock = nTestnetForkTwo + 20;
	}
	virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


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
	default:
		assert(false && "Unimplemented network");
		return;
	}
}

bool SelectParamsFromCommandLine() {

	fTestNet = GetBoolArg("-testnet", false);

	if (fTestNet) {
		SelectParams(CChainParams::TESTNET);
	}
	else {
		SelectParams(CChainParams::MAIN);
	}
	return true;
}

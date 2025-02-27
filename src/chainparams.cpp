// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The PIVX developers
// Copyright (c) 2018 The Securus developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "amount.h"
#include "base58.h"
#include "random.h"
#include "util.h"
#include "uint256.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */
static bool regenerate = false;

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (      0, uint256("00000e1dbef83856b13cfb95aa8665a2b41f6c38f4774ec78ca4ae55a7b4024e"))
    (   2000, uint256("ce01874931e0ff20d1f733f6d04488b6b5f2fcff9b06d06572da826109b87dff"))
    (   6000, uint256("3acb9c5bf7f89ba92c44f3a02db1b6e888e822c13e4ac563f12e3899a7eb64cb"))
    (   10000, uint256("369d62ff96e2695bfdc3553c0eeee96b69685d7bcc947f21df488813797e15e2"))
    (   20000, uint256("a189112ccb562cecc7c2cd31372c3d2d9415efd5c85e3f005f05ea17829d5251"))
    (   30000, uint256("f34b5f087f6065311a402214a2edf90988036f3f834d3329b5746a96c846424e"))
    (   40000, uint256("f7f121cdd614bbf213300bb308dab91ce6bf8d7e0395163558a16621b0486b52"))
    (   50000, uint256("c38b7c0fbe6cec68383232517f4b041d1e48c7bed3f6bbfba232ebdea0e0d4ec"))
    (   60000, uint256("8159c92ab2332cdb240f73e3c03e28486c8f58b17e19b8165c65700dac8d687e"))
    (   70000, uint256("8ac437b8e9944867c676a876954b85680d3de472a0ac34f315273bbf19d81c11"))
    (   80000, uint256("25991c70fc962e7d6473ce0f5291fd8bd4ffc51674d0add253c8196e506c1efc"))
    (   90000, uint256("3c1adc8ae5a3d6f69334048aaf1bc2f3e76762b343909ce45aa2ac7110514f73"))
    (   100000, uint256("b55a91181e3e36b8e4cf51fbfb1c4694324d6b152e40b4940a420ba4ce7a6e09"))
    (   110000, uint256("611382d48e924f809c0ae0c4752bea810af74775cf589f1a9e99863e1459cfa5"))
    (   120000, uint256("a15b901bafb84773a950650c558225da4f377112f00f3c47707bde66255c2d83"))
    (   130000, uint256("6b195eebf3fa60f2977e409bfe047b9cce9321dc5c8ee53a873da3f03047aa65"))
    (   140000, uint256("e7e47c9c6d3f3d783b61dbba6a48bad61c1f40db5eb8da1a1b8fe8563d4ed862"))
    (   150000, uint256("de89a8e7aec678113519481079a67a1a1e023e6b15d47942ced38a391247c8d7"))
    (   160000, uint256("fceb2702fcda45c4a0a1975cecc74b449696561b87a8e5ccc1802de11737e54f"))
    (   170000, uint256("f57e112ce8c498fd2cbf2208aa8c88c3854940874bacd7db2bc32cab87cce2f8"))
    (   180000, uint256("e2d816c0cfec1d5aab5a61dc91a775060ec1014f996a3f63fbbad18098065896"))
    (   190000, uint256("06148e5ce8281e70f0e14a6762306291b85bfb096a12aeb13117329175de1a35"))
    (   200000, uint256("3a636e1efd5358db412e39d11969231e31da038a5c4a1bb5a34c8221c264c2df"))
    (   210000, uint256("70dccb43919c9a4302ff7788a4afeb82b3fea739b1fd8d3b826538ab5b834e79"))
    (   220000, uint256("f15d7ddca7c8f957fde0fe41040e1fc928a7796fe0bb3a7a0561932390498b67"))
    (   230000, uint256("bff52d802b7bbb98f8ddc8a48fbad1810923bd7f08a892394128f119ebdf17a5"))
    (   240000, uint256("7aeefe8ff7be138d86cd65f595620d6c64e8fdd794c634547bdeb43ad38a685d"))
    (   250000, uint256("b54511a50a7ef598682b9e734a870585c0a41ae07ab4df863f6b3f4b549843db"))
    (   260000, uint256("7d3b93378061136c2b936a061f4a59e31ec9bc49ca11b897e12c48091511297c"))
    (   270000, uint256("5b2d2d3f35848560dbe3f7667b4102c8aff3894686077a82b61d4fbf439e5806"))
    (   280000, uint256("2242c5e9bc82ded577362b51e7e44068e384dae02ec1208e4a94c69309e7f86a"))
    (   290000, uint256("73cecd86be5b805e5de9731961cd37809d9466e404d888c0d6b859cec4c5161a"))
    (   300000, uint256("bda488cab11d22a4a1939e2a824a8fbecae4e157fcee1ed4c250ac16cd70d651"))
    (   310000, uint256("33a6a14c2420bde6588ea98286d2cc2baf8b7be36706b5acf1ed50e6fdb74e0e"))
    (   320000, uint256("2c2a76221572188a73b778a0b7f96e6f96aff068abb18d4d6f813e07a0a2eed6"))
    (   330000, uint256("ad6b6e2f66aeb77441f48a63e7849016faed01dcfec42c00f2988b7c95bc7440"))
    (   340000, uint256("22dca52c62a24dd187cf6354adc64beef26bfcf6e07b27868709e716c4c7a939"))
    (   350000, uint256("88eb4b9183008128f2ddc5a2dc04ec334b488a9657e6e87ede45c2564d2c02d8"))
    (   360000, uint256("c04972e28f98657779973222bde42b31fe5210676343556d705862111eb8d7e6"))
    (   370000, uint256("cd4f82f49531e9bd6093d7f042132301ab0d513330d742c344814a07ea4707a5"))
    (   380000, uint256("f416f8aab4047f1c30334ca79dc8c9c7c7c0e4ab6543df41b57be4682a6ff893"))
    (   390000, uint256("f9bead4e96a0a2e3a0f98cb846690c2780db6c7b8605b331a76b85236b832d23"))
    (   400000, uint256("b7b20f69beaaa711a023cd8be16cfa385673182f58e5aa3afae7c0fc54d0947a"))
    (   410000, uint256("e61d49da64d343bea926103564b737de6b19c29c3b5ee365981f57783ef09bbf"))
    (   420000, uint256("c578c876161dac3bb63864f248c2e0bfc318118f0bd89643025b1da049889628"))
    (   430000, uint256("cd84803520846edf828efc247366af16bac3f11fe245898674a5b59d5b269280"))
    (   440000, uint256("27d93f9b48ab69d900ee9b9d875a82b691edb2b12dbcd422e043af74e9ba8178"))
    (   450000, uint256("642d4e1adf7e6510c001f65ce41c9693a76e39cd720401aa32594e889efd4b74"))
    (   460000, uint256("a81a17b739f7a73758efd8066e958ebf040df730ed4190474d6776431a39b44f"))
    (   470000, uint256("f7db71642d6f7fde495700d575b127952cb0ae1828253dba7998d235a7d921e1"))
    (   480000, uint256("53850b7c13109afd172c4d91a14d5e3166c82ee1137a009698aa0340554f863a"))
    (   490000, uint256("ab499e9139393d7b426c93bdc2f4f96e843866d31bf7b8a0adad0ec221069562"))
    (   500000, uint256("244b2ced11ae6ccc5767f8f94edae8229803ce2d35fb3369fcc61e1bf0eaf132"))
    (   600000, uint256("44b4efc4a7a705d5551c9ab445f657eea3520d14305760a66abf95fd7e588c49"))
    (   700000, uint256("f82af61710e3d7217e2a88b8a74d3dd7322584efe12b8509fd5e93443111191d"))
    (   800000, uint256("19f1939f6a9c8bce8df99fd87c928f16bec10d94f2df9aa4929ab76e40b9fc59"))
    (   900000, uint256("5f531e5fe515ea2476f013c069969ea42d53d60a9527d61470ba560965433ecf"))
    (  1000000, uint256("1a7777fda527cb1a6d6573db310f59ff7bb8829ebb1e337ecbac26fe575f0ee9"))
    (  1004700, uint256("362924b0e5f1f310bd8343420180a1d3c15144d97adedf96f6c3a51e650fe83a"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1609322948, // * UNIX timestamp of last checkpoint block
    2000,      // * total number of transactions between genesis and last checkpoint              
    1500        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256("0x00000e1dbef83856b13cfb95aa8665a2b41f6c38f4774ec78ca4ae55a7b4024e"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1584392500,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of
    (0, uint256("410bca2b989d684a6b430d415a42546c664649117deec36f52a6750fcac72eba"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1535104494,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params(bool useModulusV1) const
{
    assert(this);
    static CBigNum bnHexModulus = 0;
    if (!bnHexModulus)
        bnHexModulus.SetHex(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsHex = libzerocoin::ZerocoinParams(bnHexModulus);
    static CBigNum bnDecModulus = 0;
    if (!bnDecModulus)
        bnDecModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsDec = libzerocoin::ZerocoinParams(bnDecModulus);

    if (useModulusV1)
        return &ZCParamsHex;

    return &ZCParamsDec;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x0f;
        pchMessageStart[1] = 0x0a;
        pchMessageStart[2] = 0xc0;
        pchMessageStart[3] = 0xe0;
        vAlertPubKey = ParseHex("0x"); // Disabled
        nDefaultPort = 20201;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // Securus starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210240;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 1 * 60;  // Securus: 1 day
        nTargetSpacing = 1 * 60;  // Securus: 1 minute
        nMaturity = 50;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 1000000000 * COIN;

        /** Height or Time Based Activations **/
        //nLastPOWBlock = 20160; // 14 days @ 1440 per day (PIVX: 259200, Phore 200)
        nLastPOWBlock = 200; // Short PoW phase before transition to PoS
        nDevFundBlock = 400000; //start dev wallet phase
        //if the lowest block height (vSortedByTimestamp[0]) is >= switch height, use new modifier calc
        // nModifierUpdateBlock = 0; // (PIVX: 615800)
        nZerocoinStartHeight = 999999999; // (PIVX: 863787, Phore 90000)
        nZerocoinStartTime = 4101895950; // December 25, 2099 9:32:30 AM GMT-06:00
        // nBlockEnforceSerialRange = 90003; //Enforce serial range starting this block (Phore 90003)
        nBlockRecalculateAccumulators = 999999999; // (PIVX: 895400, Phore 90005) //Trigger a recalculation of accumulators
        // nBlockFirstFraudulent = 90002; // (PIVX: 908000, Phore 90002) //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 999999999; // (PIVX: 891730, Phore 90005) //Last valid accumulator checkpoint
        // nBlockEnforceInvalidUTXO = 0; // (PIVX: 902850) //Start enforcing the invalid UTXO's
        // nInvalidAmountFiltered = 268200*COIN; // (PIVX: 268200) //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = 999999999; // (PIVX: 1153160) //!> The block that zerocoin v2 becomes active - roughly Tuesday, May 8, 2018 4:00:00 AM GMT
        nEnforceNewSporkKey = 1537963200; // (PIVX: 1525158000) //!> Sporks signed after (GMT): Wednesday, September 26,2018 12:00 PM must use the new spork key
        nRejectOldSporkKey = 1537966800; // (PIVX: 1527811200) //!> Fully reject old spork key after (GMT): Wednesday, September 26,2018 12:00 PM

        const char* pszTimestamp = "XSECURUS - 16.03.2020 - COVID-19 everywhere ... ";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 504365040 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 1 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 4;
        genesis.nTime = 1584392500;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 977889;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("00000e1dbef83856b13cfb95aa8665a2b41f6c38f4774ec78ca4ae55a7b4024e"));
        assert(genesis.hashMerkleRoot == uint256("44c3a39b62469d1f8a622e47077ed3c903c54e40b698528f44be5f35ea526030"));

        vSeeds.push_back(CDNSSeedData("seed", "seed.securuscoin.org"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.securuscoin.org"));
        // vSeeds.push_back(CDNSSeedData("peer1", "85.214.153.128"));
        // vSeeds.push_back(CDNSSeedData("peer2", "81.169.244.95"));
        // vSeeds.push_back(CDNSSeedData("peer3", "85.214.24.190"));
        // vSeeds.push_back(CDNSSeedData("peer4", "85.209.48.159"));
        
	
        // Securus addresses start with 'S'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,75);
        // Securus script addresses start with '3'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5);
        // Securus private keys start with '7' (uncompressed) or 'V' (compressed)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,191);
        // Securus BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // Securus BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // Securus BIP44 coin type (pending BIP44-capable wallet, use Bitcoin type)
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x00)(0xe2).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04a3f031e5c1b337c9b4d34ed595f7568acb9ec81c2b4b956abb63ee67b7a39ba25628ec76748b9cd2cfd95cc4eb90a1775500ac97d4adb6d334a54fdf8c6a8f81";
        strSporkKeyOld = "04beb92bb57470a4e6b011a291026c8cb6ce59c20b36ae5128d88b723c198443cb35cb2609eb9054f9fc49aa9f49257026cd1a09afb3fd7e1429086ab708ffb482";
        strObfuscationPoolDummyAddress = "X87q2gC9j6nNrnzCsg4aY6bHMLsT9nUhEw";
        nStartMasternodePayments = 1527634800; // 2018-05-30 00:00:00

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nZerocoinRequiredStakeDepth = 200; //The required confirmations for a zpiv to be stakable

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee

    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};

static CMainParams mainParams;
// dev wallet
std::string CChainParams::GetDevFeeRewardAddress()
{
	// return "mxe3eWJRya31h49qrATsyWx8fJBKfF6uLk";  //TESTNET
    return "XXT8EMfCATTnzK1Qr5cTiTTMDZ2UMvenpQ";  //MAINNET
}

CScript CChainParams::GetScriptForDevFeeDestination() {
    CBitcoinAddress address(GetDevFeeRewardAddress().c_str());
    assert(address.IsValid());

    CScript script = GetScriptForDestination(address.Get());
    return script;
}

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xf0;
        pchMessageStart[1] = 0xa0;
        pchMessageStart[2] = 0x0c;
        pchMessageStart[3] = 0x0e;
        vAlertPubKey = ParseHex("");
        bnProofOfWorkLimit = ~uint256(0) >> 1; // 0x207fffff, Securus testnet starting difficulty
        nSubsidyHalvingInterval = 210240;
        nDefaultPort = 20203;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Securus: 1 day
        nTargetSpacing = 60;  // Securus: 1 minute
        nLastPOWBlock = 250;
        nDevFundBlock = 300; //dev wallet testnetstart
        nMaturity = 1;
        nMasternodeCountDrift = 2;
        // nModifierUpdateBlock = 0; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 21000000 * COIN;
        nZerocoinStartHeight = 999999999;
        nZerocoinStartTime = 1530801782;
        // nBlockEnforceSerialRange = 0; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 999999999; //Trigger a recalculation of accumulators
        // nBlockFirstFraudulent = 999999999; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 999999999; //Last valid accumulator checkpoint
        // nBlockEnforceInvalidUTXO = 0; //Start enforcing the invalid UTXO's
        // nInvalidAmountFiltered = 0; //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = 999999999; //!> The block that zerocoin v2 becomes active
	nEnforceNewSporkKey = 1537963200; // (PIVX: 1525158000) //!> Sporks signed after (GMT): Wednesday, September 26,2018 12:00 PM must use the new spork key
        nRejectOldSporkKey = 1537966800; // (PIVX: 1527811200) //!> Fully reject old spork key after (GMT): Wednesday, September 26,2018 12:00 PM

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1584392500;
        genesis.nNonce = 977889;

        hashGenesisBlock = genesis.GetHash();
        
        if (regenerate) {
            hashGenesisBlock = uint256S("");
            genesis.nNonce = 0;
            if (true && (genesis.GetHash() != hashGenesisBlock)) {
                uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
                while (genesis.GetHash() > hashTarget)
                {
                    ++genesis.nNonce;
                    if (genesis.nNonce == 0)
                    {
                        ++genesis.nTime;
                    }
                }
                std::cout << "// Testnet ---";
                std::cout << " nonce: " << genesis.nNonce;
                std::cout << " time: " << genesis.nTime;
                std::cout << " hash: 0x" << genesis.GetHash().ToString().c_str();
                std::cout << " merklehash: 0x"  << genesis.hashMerkleRoot.ToString().c_str() <<  "\n";

            }
        } else {
            LogPrintf("Testnet ---\n");
            LogPrintf(" nonce: %u\n", genesis.nNonce);
            LogPrintf(" time: %u\n", genesis.nTime);
            LogPrintf(" hash: 0x%s\n", genesis.GetHash().ToString().c_str());
            LogPrintf(" merklehash: 0x%s\n", genesis.hashMerkleRoot.ToString().c_str());
            assert(hashGenesisBlock == uint256("0x00000e1dbef83856b13cfb95aa8665a2b41f6c38f4774ec78ca4ae55a7b4024e"));
            assert(genesis.hashMerkleRoot == uint256("0x44c3a39b62469d1f8a622e47077ed3c903c54e40b698528f44be5f35ea526030"));
        }

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("peer1", "85.214.153.128"));
        vSeeds.push_back(CDNSSeedData("peer2", "81.169.244.95"));
        //vSeeds.push_back(CDNSSeedData("peer3", "85.214.24.190"));
        
        vSeeds.push_back(CDNSSeedData("peer4", "85.209.48.159"));
        vSeeds.push_back(CDNSSeedData("felix", "85.214.24.190"));
	

        // Testnet Securus addresses start with 'm' or 'n'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        // Testnet Securus script addresses start with '2'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        // Testnet private keys start with '9' (uncompressed) or 'c' (compressed)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        // Testnet Securus BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet Securus BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Testnet Securus BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fSkipProofOfWorkCheck = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "040e0c130f23e1eaf814706f03bcb5f93fdb51ef7b79806cb84703d81dc144497616468417a1585bb8c4034ca4dc0cf4c17424832151e607763c96b9cafa238f1f";
        strSporkKeyOld = "04beb92bb57470a4e6b011a291026c8cb6ce59c20b36ae5128d88b723c198443cb35cb2609eb9054f9fc49aa9f49257026cd1a09afb3fd7e1429086ab708ffb482";
        strObfuscationPoolDummyAddress = "m57cqfGRkekRyDRNeJiLtYVEbvhXrNbmox";
        nStartMasternodePayments = 1527634800; //30th May 2018 00:00:00
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xf0;
        pchMessageStart[1] = 0x0a;
        pchMessageStart[2] = 0xc0;
        pchMessageStart[3] = 0x0e;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Securus: 1 day
        nTargetSpacing = 60;  // Securus: 1 minute
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nDefaultPort = 14505;

        genesis.nTime = 1535104494;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 3;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("9d9d3641c99094c2a586cb3416f4a8068069b483328b8d930a3de096797e4208"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 20109;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        // fSkipProofOfWorkCheck = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}

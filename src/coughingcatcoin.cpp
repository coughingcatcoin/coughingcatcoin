// Copyright (c) 2015 The Coughingcatcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/random/uniform_int.hpp>
#include <boost/random/mersenne_twister.hpp>

#include "policy/policy.h"
#include "arith_uint256.h"
#include "coughingcatcoin.h"
#include "txmempool.h"
#include "util.h"
#include "validation.h"
#include "coughingcatcoin-fees.h"

int static generateMTRandom(unsigned int s, int range)
{
    boost::mt19937 gen(s);
    boost::uniform_int<> dist(1, range);
    return dist(gen);
}

// Coughingcatcoin: Normally minimum difficulty blocks can only occur in between
// retarget blocks. However, once we introduce Digishield every block is
// a retarget, so we need to handle minimum difficulty on all blocks.
bool AllowDigishieldMinDifficultyForBlock(const CBlockIndex* pindexLast, const CBlockHeader *pblock, const Consensus::Params& params)
{
    // check if the chain allows minimum difficulty blocks
    if (!params.fPowAllowMinDifficultyBlocks)
        return false;

    // check if the chain allows minimum difficulty blocks on recalc blocks
    if (pindexLast->nHeight < 157500)
    // if (!params.fPowAllowDigishieldMinDifficultyBlocks)
        return false;

    // Allow for a minimum block time if the elapsed time > 2*nTargetSpacing
    return (pblock->GetBlockTime() > pindexLast->GetBlockTime() + params.nPowTargetSpacing*2);
}

unsigned int CalculateCoughingcatcoinNextWorkRequired(const CBlockIndex* pindexLast, int64_t nFirstBlockTime, const Consensus::Params& params)
{
    int nHeight = pindexLast->nHeight + 1;
    const int64_t retargetTimespan = params.nPowTargetTimespan;
    const int64_t nActualTimespan = pindexLast->GetBlockTime() - nFirstBlockTime;
    int64_t nModulatedTimespan = nActualTimespan;
    int64_t nMaxTimespan;
    int64_t nMinTimespan;

    if (params.fDigishieldDifficultyCalculation) //DigiShield implementation - thanks to RealSolid & WDC for this code
    {
        // amplitude filter - thanks to daft27 for this code
        nModulatedTimespan = retargetTimespan + (nModulatedTimespan - retargetTimespan) / 8;

        nMinTimespan = retargetTimespan - (retargetTimespan / 4);
        nMaxTimespan = retargetTimespan + (retargetTimespan / 2);
    } else if (nHeight > 10000) {
        nMinTimespan = retargetTimespan / 4;
        nMaxTimespan = retargetTimespan * 4;
    } else if (nHeight > 5000) {
        nMinTimespan = retargetTimespan / 8;
        nMaxTimespan = retargetTimespan * 4;
    } else {
        nMinTimespan = retargetTimespan / 16;
        nMaxTimespan = retargetTimespan * 4;
    }

    // Limit adjustment step
    if (nModulatedTimespan < nMinTimespan)
        nModulatedTimespan = nMinTimespan;
    else if (nModulatedTimespan > nMaxTimespan)
        nModulatedTimespan = nMaxTimespan;

    // Retarget
    const arith_uint256 bnPowLimit = UintToArith256(params.powLimit);
    arith_uint256 bnNew;
    arith_uint256 bnOld;
    bnNew.SetCompact(pindexLast->nBits);
    bnOld = bnNew;
    bnNew *= nModulatedTimespan;
    bnNew /= retargetTimespan;

    if (bnNew > bnPowLimit)
        bnNew = bnPowLimit;

    return bnNew.GetCompact();
}

bool CheckAuxPowProofOfWork(const CBlockHeader& block, const Consensus::Params& params)
{
    /* Except for legacy blocks with full version 1, ensure that
       the chain ID is correct.  Legacy blocks are not allowed since
       the merge-mining start, which is checked in AcceptBlockHeader
       where the height is known.  */
    if (!block.IsLegacy() && params.fStrictChainId && block.GetChainId() != params.nAuxpowChainId)
        return error("%s : block does not have our chain ID"
                     " (got %d, expected %d, full nVersion %d)",
                     __func__, block.GetChainId(),
                     params.nAuxpowChainId, block.nVersion);

    /* If there is no auxpow, just check the block hash.  */
    if (!block.auxpow) {
        if (block.IsAuxpow())
            return error("%s : no auxpow on block with auxpow version",
                         __func__);

        if (!CheckProofOfWork(block.GetPoWHash(), block.nBits, params))
            return error("%s : non-AUX proof of work failed", __func__);

        return true;
    }

    /* We have auxpow.  Check it.  */

    if (!block.IsAuxpow())
        return error("%s : auxpow on block with non-auxpow version", __func__);

    if (!block.auxpow->check(block.GetHash(), block.GetChainId(), params))
        return error("%s : AUX POW is not valid", __func__);
    if (!CheckProofOfWork(block.auxpow->getParentBlockPoWHash(), block.nBits, params))
        return error("%s : AUX proof of work failed", __func__);

    return true;
}

CAmount GetCoughingcatcoinBlockSubsidy(int nHeight, const Consensus::Params& consensusParams, uint256 prevHash)
{
    int halvings = nHeight / consensusParams.nSubsidyHalvingInterval;

    // if (halvings >= 64)
    //     return 0;

    if(nHeight <= 51){
        return 938000000 * COIN;
    }

    if(nHeight <= 50000){
        return 500000 * COIN;
    }

    if(nHeight <= 100000){
        return 250000 * COIN;
    }

    if(nHeight <= 150000){
        return 125000 * COIN;
    }

    if(nHeight <= 200000){
        return 62500 * COIN;
    }

    if(nHeight <= 202000){
        return 31250 * COIN;
    }

    if(nHeight <= 210000){
        return 656200 * COIN;
    }

    if(nHeight <= 310000){
        return 1.5 * COIN;
    }

    if(nHeight <= 410000){
        return 1.25 * COIN;
    }

    if(nHeight <= 510000){
        return 62500000;
    }

    if(nHeight <= 610000){
        return 31250000;
    }

    if(nHeight <= 710000){
        return 15625000;
    }

    if(nHeight <= 810000){
        return 7812500;
    }

    if(nHeight <= 910000){
        return 3906250;
    }

    if(nHeight <= 1010000){
        return 1953125;
    }

    if(nHeight <= 1110000){
        return 976563;
    }

    if(nHeight <= 1210000){
        return 488281;
    }

    if(nHeight <= 1310000){
        return 244141;
    }

    if(nHeight <= 1410000){
        return 122070;
    }

    if(nHeight <= 1510000){
        return 61035;
    }

    if(nHeight <= 1610000){
        return 30518;
    }

    if(nHeight <= 1710000){
        return 15259;
    }

    if(nHeight <= 1810000){
        return 7629;
    }

    if(nHeight <= 1910000){
        return 3815;
    }

    if(nHeight <= 2010000){
        return 1907;
    }

    if(nHeight <= 2110000){
        return 954;
    }

    if(nHeight <= 2210000){
        return 477;
    }

    if(nHeight <= 2310000){
        return 238;
    }

    if(nHeight <= 2410000){
        return 119;
    }

    if(nHeight <= 2510000){
        return 60;
    }

    if(nHeight <= 2610000){
        return 30;
    }

    if(nHeight <= 2710000){
        return 15;
    }

    if(nHeight <= 2810000){
        return 7;
    }

    if(nHeight <= 2910000){
        return 4;
    }

    if(nHeight <= 3010000){
        return 2;
    }

    if(nHeight <= 3110000){
        return 1;
    }

    // if(nHeight <= 3210000){
    //     return 0;
    // }

    // if(nHeight <= 3310000){
    //     return 0;
    // }

    // if(nHeight <= 3410000){
    //     return 0;
    // }

    // if(nHeight <= 3510000){
    //     return  0;
    // }

    // if(nHeight <= 3600000){
    //     return  0;
    // }

    return 0;


    // CAmount nSubsidy = 5000 * COIN;
    // // Subsidy is cut in half every 210,000 blocks which will occur approximately every 4 years.
    // nSubsidy >>= halvings;
    // return nSubsidy;
}



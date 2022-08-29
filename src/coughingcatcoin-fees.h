// Copyright (c) 2021 The Coughingcatcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "amount.h"
#include "chain.h"
#include "chainparams.h"

#ifdef ENABLE_WALLET
CFeeRate GetCoughingcatcoinWalletFeeRate();
CAmount GetCoughingcatcoinMinWalletFee(unsigned int nBytes_);
#endif
CAmount GetCoughingcatcoinMinRelayFee(const CTransaction& tx, unsigned int nBytes, bool fAllowFree);
CAmount GetCoughingcatcoinDustFee(const std::vector<CTxOut> &vout, CFeeRate &baseFeeRate);

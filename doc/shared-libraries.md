Shared Libraries
================

## coughingcatcoinconsensus

The purpose of this library is to make the verification functionality that is critical to Coughingcatcoin's consensus available to other applications, e.g. to language bindings.

### API

The interface is defined in the C header `coughingcatcoinconsensus.h` located in  `src/script/coughingcatcoinconsensus.h`.

#### Version

`coughingcatcoinconsensus_version` returns an `unsigned int` with the API version *(currently at an experimental `0`)*.

#### Script Validation

`coughingcatcoinconsensus_verify_script` returns an `int` with the status of the verification. It will be `1` if the input script correctly spends the previous output `scriptPubKey`.

##### Parameters
- `const unsigned char *scriptPubKey` - The previous output script that encumbers spending.
- `unsigned int scriptPubKeyLen` - The number of bytes for the `scriptPubKey`.
- `const unsigned char *txTo` - The transaction with the input that is spending the previous output.
- `unsigned int txToLen` - The number of bytes for the `txTo`.
- `unsigned int nIn` - The index of the input in `txTo` that spends the `scriptPubKey`.
- `unsigned int flags` - The script validation flags *(see below)*.
- `coughingcatcoinconsensus_error* err` - Will have the error/success code for the operation *(see below)*.

##### Errors
- `coughingcatcoinconsensus_ERR_OK` - No errors with input parameters *(see the return value of `coughingcatcoinconsensus_verify_script` for the verification status)*
- `coughingcatcoinconsensus_ERR_TX_INDEX` - An invalid index for `txTo`
- `coughingcatcoinconsensus_ERR_TX_SIZE_MISMATCH` - `txToLen` did not match with the size of `txTo`
- `coughingcatcoinconsensus_ERR_DESERIALIZE` - An error deserializing `txTo`
- `coughingcatcoinconsensus_ERR_AMOUNT_REQUIRED` - Input amount is required if WITNESS is used

### Example Implementations
- [NBitcoin](https://github.com/NicolasDorier/NBitcoin/blob/master/NBitcoin/Script.cs#L814) (.NET Bindings)
- [node-libcoughingcatcoinconsensus](https://github.com/bitpay/node-libcoughingcatcoinconsensus) (Node.js Bindings)
- [java-libcoughingcatcoinconsensus](https://github.com/dexX7/java-libcoughingcatcoinconsensus) (Java Bindings)
- [coughingcatcoinconsensus-php](https://github.com/Bit-Wasp/coughingcatcoinconsensus-php) (PHP Bindings)

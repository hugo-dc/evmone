// evmone: Fast Ethereum Virtual Machine implementation
// Copyright 2023 The evmone Authors.
// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <cassert>
#include <system_error>

namespace evmone::state
{

enum ErrorCode : int
{
    SUCCESS = 0,
    INTRINSIC_GAS_TOO_LOW,
    TX_TYPE_NOT_SUPPORTED,
    INSUFFICIENT_FUNDS,
    NONCE_HAS_MAX_VALUE,
    NONCE_TOO_HIGH,
    NONCE_TOO_LOW,
    TIP_GT_FEE_CAP,
    FEE_CAP_LESS_THEN_BLOCKS,
    GAS_LIMIT_REACHED,
    SENDER_NOT_EOA,
    INIT_CODE_SIZE_LIMIT_EXCEEDED,
    create_blob_tx,
    empty_blob_hashes_list,
    invalid_blob_hash_version,
    insufficient_data_funds,
    UNKNOWN_ERROR,
};

/// Obtains a reference to the static error category object for evmone errors.
inline const std::error_category& evmone_category() noexcept
{
    struct Category : std::error_category
    {
        [[nodiscard]] const char* name() const noexcept final { return "evmone"; }

        [[nodiscard]] std::string message(int ev) const noexcept final
        {
            switch (ev)
            {
            case SUCCESS:
                return "";
            case INTRINSIC_GAS_TOO_LOW:
                return "intrinsic gas too low";
            case TX_TYPE_NOT_SUPPORTED:
                return "transaction type not supported";
            case INSUFFICIENT_FUNDS:
                return "insufficient funds for gas * price + value";
            case NONCE_HAS_MAX_VALUE:
                return "nonce has max value:";
            case NONCE_TOO_HIGH:
                return "nonce too high";
            case NONCE_TOO_LOW:
                return "nonce too low";
            case TIP_GT_FEE_CAP:
                return "max priority fee per gas higher than max fee per gas";
            case FEE_CAP_LESS_THEN_BLOCKS:
                return "max fee per gas less than block base fee";
            case GAS_LIMIT_REACHED:
                return "gas limit reached";
            case SENDER_NOT_EOA:
                return "sender not an eoa:";
            case INIT_CODE_SIZE_LIMIT_EXCEEDED:
                return "max initcode size exceeded";
            case create_blob_tx:
                return "blob transaction must not be a create transaction";
            case empty_blob_hashes_list:
                return "empty blob hashes list";
            case invalid_blob_hash_version:
                return "invalid blob hash version";
            case insufficient_data_funds:
                return "insufficient data funds";
            case UNKNOWN_ERROR:
                return "Unknown error";
            default:
                assert(false);
                return "Wrong error code";
            }
        }
    };

    static const Category category_instance;
    return category_instance;
}

/// Creates error_code object out of an evmone error code value.
/// This is used by std::error_code to implement implicit conversion
/// evmone::ErrorCode -> std::error_code, therefore the definition is
/// in the global namespace to match the definition of ethash_errc.
inline std::error_code make_error_code(ErrorCode errc) noexcept
{
    return {errc, evmone_category()};
}

}  // namespace evmone::state

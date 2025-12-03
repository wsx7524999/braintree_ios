@import Foundation;

#import "BTAppSwitching.h"
#import "BTAppSwitchErrors.h"

@class BTCoinbasePaymentMethod;

/// Block type for handling successful account linking operations
typedef void (^BTCoinbaseAccountLinkSuccessBlock)(void);

/// Block type for handling failed account linking operations
typedef void (^BTCoinbaseAccountLinkFailureBlock)(NSError *error);

/// Block type for handling successful account verification operations
/// @param isLinked Indicates whether an account is currently linked
typedef void (^BTCoinbaseAccountVerificationBlock)(BOOL isLinked);

/// Manages the communication with the Coinbase app or browser for authorization
///
/// This is a beta integration option. For details, see https://www.braintreepayments.com/features/coinbase
///
/// @see BTAppSwitching
@interface BTCoinbase : NSObject <BTAppSwitching>

@property (nonatomic, assign) BOOL storeInVault;

/// Dynamically disable Coinbase support on the client-side,
/// e.g. for certain customers, geographies, devices, etc.
///
/// Example:
/// `[BTCoinbase sharedCoinbase].disabled = [CoinbaseOAuth isAppOAuthAuthenticationAvailable] ? NO : YES;`
@property (nonatomic, assign) BOOL disabled;

/// Indicates whether a Coinbase account is currently linked
@property (nonatomic, readonly, assign) BOOL isAccountLinked;

+ (instancetype)sharedCoinbase;

/// Checks whether the Coinbase app is installed (and accepting app switch authorization)
/// and Braintree is configured for Coinbase app switch. This requires a returnURLScheme
/// to be set and for Coinbase to be enabled in your Braintree Control Panel.
///
/// @param client A BTClient
///
/// @return YES if the Coinbase native app is available for app switch.
///
/// @see `+[Braintree setReturnURLScheme:]`
- (BOOL)providerAppSwitchAvailableForClient:(BTClient *)client;

#pragma mark - Account Association

/// Links a user's Coinbase account using the provided payment method.
///
/// This method associates the user's Coinbase account with the current Braintree customer,
/// enabling future payments using the linked account.
///
/// @param paymentMethod The BTCoinbasePaymentMethod obtained from Coinbase authorization
/// @param successBlock  Block called when account linking succeeds
/// @param failureBlock  Block called when account linking fails, with error details
///
/// @note The payment method must be valid and obtained through proper Coinbase OAuth flow
- (void)linkAccountWithPaymentMethod:(BTCoinbasePaymentMethod *)paymentMethod
                             success:(BTCoinbaseAccountLinkSuccessBlock)successBlock
                             failure:(BTCoinbaseAccountLinkFailureBlock)failureBlock;

/// Unlinks the currently associated Coinbase account.
///
/// This method removes the association between the user's Coinbase account
/// and the current Braintree customer.
///
/// @param successBlock Block called when account unlinking succeeds
/// @param failureBlock Block called when account unlinking fails, with error details
- (void)unlinkAccountWithSuccess:(BTCoinbaseAccountLinkSuccessBlock)successBlock
                         failure:(BTCoinbaseAccountLinkFailureBlock)failureBlock;

/// Verifies whether a Coinbase account is currently linked to the Braintree customer.
///
/// This method asynchronously checks the account association status.
///
/// @param completionBlock Block called with the verification result (YES if linked, NO otherwise)
- (void)verifyAccountLinkStatus:(BTCoinbaseAccountVerificationBlock)completionBlock;

@end

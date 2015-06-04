//
//  ATLWatchconversationInterfaceController.h
//  Layer Messenger
//
//  Created by Kevin Coleman on 5/29/15.
//  Copyright (c) 2015 Layer. All rights reserved.
//

#import <WatchKit/WatchKit.h>
#import <Foundation/Foundation.h>
#import <LayerKit/LayerKit.h>
#import "ATLParticipant.h"

@class ATLConversationInterfaceController;

//---------------------------------------
/// @name Delegate
///---------------------------------------

@protocol ATLConversationInterfaceControllerDelegate <NSObject>

@optional
/**
 @abstract Informs the delegate that a user successfully sent an `LYRMessage` object.
 @param conversationInterfaceController The `ATLConversationInterfaceController` in which the message was sent.
 @param message The `LYRMessage` object that was sent via Layer.
 */
- (void)conversationInterfaceController:(ATLConversationInterfaceController *)viewController didSendMessage:(LYRMessage *)message;

/**
 @abstract Informs the delegate that an `LYRMessage` object send attempt failed.
 @param conversationInterfaceController The `ATLConversationInterfaceController` in which the message failed to send.
 @param message The `LYRMessage` object which was attempted to be sent via Layer.
 @param error The `NSError` object describing why send failed.
 */
- (void)conversationInterfaceController:(ATLConversationInterfaceController *)viewController didFailSendingMessage:(LYRMessage *)message error:(NSError *)error;

/**
 @abstract Informs the delegate that an `LYRMessage` object was tapped.
 @param conversationInterfaceController The `ATLConversationInterfaceController` in which the message failed to send.
 @param message The `LYRMessage` object which that was tapped.
 */
- (void)conversationInterfaceController:(ATLConversationInterfaceController *)viewController didSelectMessage:(LYRMessage *)message;

@end

///---------------------------------------
/// @name Data Source
///---------------------------------------

@protocol ATLConversationInterfaceControllerDataSource <NSObject>

/**
 @abstract Asks the data source for an object conforming to the `ATLParticipant` protocol for a given identifier.
 @param conversationInterfaceController The `ATLConversationInterfaceController` requesting the object.
 @param participantForIdentifier The participant identifier.
 @return An object conforming to the `ATLParticipant` protocol.
 */
- (id<ATLParticipant>)conversationInterfaceController:(ATLConversationInterfaceController *)conversationInterfaceController participantForIdentifier:(NSString *)participantIdentifier;

/**
 @abstract Asks the data source for an `NSAttributedString` representation of a given date.
 @param conversationInterfaceController The `ATLConversationInterfaceController` requesting the string.
 @param date The `NSDate` object to be displayed as a string.
 @return an `NSAttributedString` representing the given date.
 @discussion The date string will be displayed above message cells in section headers. The date represents the `sentAt` date of a message object.
 The string can be customized to appear in whichever format your application requires.
 */
- (NSAttributedString *)conversationInterfaceController:(ATLConversationInterfaceController *)conversationInterfaceController attributedStringForDisplayOfDate:(NSDate *)date;

/**
 @abstract Asks the data source for an `NSAttributedString` representation of a given `LYRRecipientStatus`.
 @param conversationInterfaceController The `ATLConversationInterfaceController` requesting the string.
 @param recipientStatus The `LYRRecipientStatus` object to be displayed as a question
 string.
 @return An `NSAttributedString` representing the give recipient status.
 @discussion The recipient status string will be displayed below message the most recent message sent by the authenticated user.
 */
- (NSAttributedString *)conversationInterfaceController:(ATLConversationInterfaceController *)conversationInterfaceController attributedStringForDisplayOfRecipientStatus:(NSDictionary *)recipientStatus;

@optional

/**
 @abstract Asks the data source to configure the default query used to fetch content for the controller if necessary.
 @discussion The `LYRconversationInterfaceController` uses the following default query:
 
 LYRQuery *query = [LYRQuery queryWithQueryableClass:[LYRMessage class]];
 query.predicate = [LYRPredicate predicateWithProperty:@"conversation" predicateOperator:LYRPredicateOperatorIsEqualTo value:self.conversation];
 query.sortDescriptors = @[[NSSortDescriptor sortDescriptorWithKey:@"position" ascending:YES]];
 
 Applications that require advanced query configuration can do so by implementing this data source method.
 
 @param viewController The `ATLConversationInterfaceController` requesting the configuration.
 @param defaultQuery An `LYRQuery` object with the default configuration for the controller.
 @return An `LYRQuery` object with any additional configuration.
 @raises `NSInvalidArgumentException` if an `LYRQuery` object is not returned.
 */
- (LYRQuery *)conversationInterfaceController:(ATLConversationInterfaceController *)viewController willLoadWithQuery:(LYRQuery *)defaultQuery;

@end

@interface ATLConversationInterfaceController : WKInterfaceController

@property (strong, nonatomic) IBOutlet WKInterfaceTable *messageTable;

@property (nonatomic, weak) id<ATLConversationInterfaceControllerDataSource>dataSource;

@property (nonatomic, weak) id<ATLConversationInterfaceControllerDelegate>delegate;

@property (nonatomic) LYRClient *layerClient;

@property (nonatomic) LYRConversation *conversation;

@property (strong, nonatomic) IBOutlet WKInterfaceButton *replyButton;

- (void)configureConversationViewController;

@end
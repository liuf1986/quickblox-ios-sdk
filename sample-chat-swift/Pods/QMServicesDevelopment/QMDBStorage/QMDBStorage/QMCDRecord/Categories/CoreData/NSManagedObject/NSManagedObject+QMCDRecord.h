//
//
//  Created by Injoit on 11/15/09.
//  Copyright (c) 2015 Quickblox Team. All rights reserved.
//

#import <CoreData/CoreData.h>
#import "QMCDRecord.h"
#import "QMCDRecordMOGeneratorProtocol.h"
#import "QMCDRecordDeprecated.h"

@protocol QMCDRecordManagedObjectProtocol <NSObject>

@optional
/**
 Work around for situation with inserting the same object into many nested contexts. This will be called once, while awakeFromInsert has the potential to be called mutliple times for the same insert.
 */
- (void) QM_awakeFromCreation;

@end

/** 
 Categories that simplify working with the NSManagedObject class.

 @since Available in v1.0 and later.
 */
@interface NSManagedObject (QMCDRecord) <QMCDRecordMOGeneratorProtocol, QMCDRecordManagedObjectProtocol>

/**
 @name Entity Information
 */

/** 
 If you want to customize the entity name that is returned, you can override either `+ (NSString *) QM_entityName` or `+ (NSString *) entityName` in your `NSManagedObject` subclasses. `+ (NSString *) entityName` is declared in the default mogenerator templates.

 @return Name of the managed object's entity, or if that is unavailable the name of the managed object's class as a string

 @since Available in v2.0 and later.
 */
+ (NSString *) QM_entityName;

+ (NSEntityDescription *) QM_entityDescription;
+ (NSEntityDescription *) QM_entityDescriptionInContext:(NSManagedObjectContext *)context;

+ (NSArray *) QM_propertiesNamed:(NSArray *)properties;
+ (NSArray *) QM_propertiesNamed:(NSArray *)properties inContext:(NSManagedObjectContext *)context;

/**
 @name Fetch Requests
 */

+ (NSArray *) QM_executeFetchRequest:(NSFetchRequest *)request;
+ (NSArray *) QM_executeFetchRequest:(NSFetchRequest *)request inContext:(NSManagedObjectContext *)context;
+ (id) QM_executeFetchRequestAndReturnFirstObject:(NSFetchRequest *)request;
+ (id) QM_executeFetchRequestAndReturnFirstObject:(NSFetchRequest *)request inContext:(NSManagedObjectContext *)context;

/** 
 @name Creating Entities
 */

+ (instancetype) QM_createEntity;
+ (instancetype) QM_createEntityInContext:(NSManagedObjectContext *)context;

/** 
 Create a new entity using the provided entity description.

 @discussion Useful for creating entities that are not attached to a managed object context — just pass a valid entity description and a nil context.

 @param entityDescription Entity description or nil. A valid context must be provided if this parameter is nil.
 @param context Managed Object Context or nil. A valid entity description must be provided if this parameter is nil.

 @return a new instance of the current NSManagedObject subclass
 */
+ (instancetype) QM_createEntityWithDescription:(NSEntityDescription *)entityDescription inContext:(NSManagedObjectContext *)context;

/**
 Check if an object has been saved to at least one persistent store
 
 @return YES if object has a permanent ID
 */
- (BOOL) QM_isTemporaryObject;

/**
 @name Deleting Entities
 */

/** 
 Checks the `isDeleted` and `managedObjectContext` methods to determine if the managed object has been deleted.

 @return YES if the object has been deleted, otherwise NO

 @since Available in v2.3 and later.
 */
- (BOOL) QM_isEntityDeleted;

/** 
 Deletes the entity from the default context of the default stack.
 
 The default stack must be setup and available for use before using this method.

 @return YES if the delete was performed successfully, otherwise NO.

 @since Available in v1.8 and later.
 */
- (BOOL) QM_deleteEntity;

/**
 Deletes the entity from the supplied context.

 @param context Managed object context

 @return YES if the delete was performed successfully, otherwise NO.

 @since Available in v2.3 and later.
 */
- (BOOL) QM_deleteEntityInContext:(NSManagedObjectContext *)context;

/**
 Deletes any entities matching the passed predicate from the default context of the default stack.

 @param predicate Predicate to evaluate objects against

 @return YES if the delete was performed successfully, otherwise NO.

 @since Available in v1.8 and later.
 */
+ (BOOL) QM_deleteAllMatchingPredicate:(NSPredicate *)predicate;

/**
 Deletes all entities matching the passed predicate from the supplied context.

 @param predicate Predicate to evaluate objects against
 @param context   Managed object context

 @return YES if the delete was performed successfully, otherwise NO.

 @since Available in v1.8 and later.
 */
+ (BOOL) QM_deleteAllMatchingPredicate:(NSPredicate *)predicate inContext:(NSManagedObjectContext *)context;

/**
 Deletes all entities with a class that matches this subclass from the default context of the default stack.

 @return YES if the delete was performed successfully, otherwise NO.

 @since Available in v1.8 and later.
 */
+ (BOOL) QM_truncateAll;

/**
 Deletes all entities with a class that matches this subclass from the supplied context.

 @param context Managed object context

 @return YES if the delete was performed successfully, otherwise NO.

 @since Available in v1.8 and later.
 */
+ (BOOL) QM_truncateAllInContext:(NSManagedObjectContext *)context;

/**
 @name Sorting Entities
 */

/**
 Initializes an array of ascending sort descriptors for the supplied attributes.

 @param attributesToSortBy Array of attribute names to sort by.

 @return Array of sort descriptors.

 @since Available in v1.8 and later.
 */
+ (NSArray *) QM_ascendingSortDescriptors:(NSArray *)attributesToSortBy;

/**
 Initializes an array of descending sort descriptors for the supplied attributes.

 @param attributesToSortBy Array of attribute names to sort by.

 @return Array of sort descriptors.

 @since Available in v1.8 and later.
 */
+ (NSArray *) QM_descendingSortDescriptors:(NSArray *)attributesToSortBy;

/**
 Initializes an array of sort descriptors for the supplied attributes, sorted according to the supplied `ascending` value.

 @param ascending          Whether to sort the descriptors ascending (`YES`) or descending (`NO`).
 @param attributesToSortBy Array of attribute names to sort by.

 @return Array of sort descriptors.

 @since Available in v2.3 and later.
 */
+ (NSArray *) QM_sortAscending:(BOOL)ascending attributes:(NSArray *)attributesToSortBy;

/**
 @name Working Across Contexts
 */

/** 
 If the object has a temporary object identifier, this method requests a permanent object identifier from the object's current context.

 @since Available in v2.1 and later.
 */
- (void) QM_obtainPermanentObjectID;

/**
 Updates the persistent properties of a managed object to use the latest values from the persistent store.

 @since Available in v3.0 and later.
 */
- (void) QM_refresh;

/** 
 Retrieves an instance of the current managed object from another context.

 If the current managed object's context matches `otherContext`, self will be returned immediately.

 If the current managed object has a temporary ID, an exception with name "NSObjectInaccessibleException" will be thrown.

 @param otherContext Valid managed object context

 @return Managed object from the supplied context

 @since Available in v1.8 and later.
 */
- (instancetype) QM_inContext:(NSManagedObjectContext *)otherContext;

/** 
 If the current managed object has a temporary ID, returns self immediately otherwise calls `- QM_inContext:` on self with the supplied managed object context.

 @param otherContext Valid managed object context
 
 @return Managed object from the supplied context

 @since Available in v3.0 and later.
 */
- (instancetype) QM_inContextIfTemporaryObject:(NSManagedObjectContext *)otherContext;

/**
 @name Validation
 */

/**
 Wrapper around `-validateForInsert:` that automatically logs any errors.

 @return YES if the entity is valid for insertion, otherwise NO.

 @since Available in v3.0 and later.
 */
- (BOOL) QM_isValidForInsert;

/**
 Wrapper around `-validateForUpdate:` that automatically logs any errors.

 @return YES if the entity is valid for updating, otherwise NO.

 @since Available in v3.0 and later.
 */
- (BOOL) QM_isValidForUpdate;

@end

@interface NSManagedObject (QMCDRecordDeprecated)

+ (instancetype) QM_createInContext:(NSManagedObjectContext *)context QM_DEPRECATED_IN_3_0_PLEASE_USE("QM_createEntityInContext:");
- (instancetype) QM_inContextIfTempObject:(NSManagedObjectContext *)otherContext QM_DEPRECATED_IN_3_0_PLEASE_USE("QM_inContextIfTemporaryObject:");
- (BOOL) QM_deleteInContext:(NSManagedObjectContext *)context QM_DEPRECATED_IN_3_0_PLEASE_USE("QM_deleteEntityInContext:");

@end

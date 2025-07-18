#import <LegacyComponents/TGMediaEditingContext.h>
#import <LegacyComponents/TGPhotoToolbarView.h>
#import <LegacyComponents/LegacyComponentsContext.h>
#import <LegacyComponents/TGOverlayController.h>

#import <AVFoundation/AVFoundation.h>

@class SSignal;
@class PGCameraShotMetadata;
@class TGPhotoEditorController;
@class AVPlayer;

@protocol TGPhotoPaintStickersContext;
@protocol TGPhotoDrawingEntitiesView;

typedef enum {
    TGPhotoEditorControllerGenericIntent = 0,
    TGPhotoEditorControllerAvatarIntent = (1 << 0),
    TGPhotoEditorControllerSignupAvatarIntent = (1 << 1),
    TGPhotoEditorControllerFromCameraIntent = (1 << 2),
    TGPhotoEditorControllerWebIntent = (1 << 3),
    TGPhotoEditorControllerVideoIntent = (1 << 4),
    TGPhotoEditorControllerForumAvatarIntent = (1 << 5),
    TGPhotoEditorControllerSuggestedAvatarIntent = (1 << 6),
    TGPhotoEditorControllerSuggestingAvatarIntent = (1 << 7),
    TGPhotoEditorControllerWallpaperIntent = (1 << 8)
} TGPhotoEditorControllerIntent;

@interface TGPhotoEditorController : TGOverlayController

@property (nonatomic, strong) TGMediaEditingContext *editingContext;
@property (nonatomic, strong) id<TGPhotoPaintStickersContext> stickersContext;

@property (nonatomic, copy) UIView *(^beginTransitionIn)(CGRect *referenceFrame, UIView **parentView);
@property (nonatomic, copy) void (^finishedTransitionIn)(void);
@property (nonatomic, copy) UIView *(^beginTransitionOut)(CGRect *referenceFrame, UIView **parentView, bool saving);
@property (nonatomic, copy) void (^finishedTransitionOut)(bool saved);

@property (nonatomic, copy) void (^onDismiss)();

@property (nonatomic, copy) void (^beginCustomTransitionOut)(CGRect, UIView *, void(^)(void));

@property (nonatomic, copy) SSignal *(^requestThumbnailImage)(id<TGMediaEditableItem> item);
@property (nonatomic, copy) SSignal *(^requestOriginalScreenSizeImage)(id<TGMediaEditableItem> item, NSTimeInterval position);
@property (nonatomic, copy) SSignal *(^requestOriginalFullSizeImage)(id<TGMediaEditableItem> item, NSTimeInterval position);
@property (nonatomic, copy) SSignal *(^requestMetadata)(id<TGMediaEditableItem> item);
@property (nonatomic, copy) id<TGMediaEditAdjustments> (^requestAdjustments)(id<TGMediaEditableItem> item);

@property (nonatomic, copy) UIImage *(^requestImage)(void);
@property (nonatomic, copy) void (^requestToolbarsHidden)(bool hidden, bool animated);

@property (nonatomic, copy) void (^captionSet)(NSAttributedString *caption);

@property (nonatomic, copy) void (^willFinishEditing)(id<TGMediaEditAdjustments> adjustments, id temporaryRep, bool hasChanges);
@property (nonatomic, copy) void (^didFinishRenderingFullSizeImage)(UIImage *fullSizeImage);
@property (nonatomic, copy) void (^didFinishEditing)(id<TGMediaEditAdjustments> adjustments, UIImage *resultImage, UIImage *thumbnailImage, bool hasChanges, void(^commit)(void));
@property (nonatomic, copy) void (^didFinishEditingVideo)(AVAsset *asset, id<TGMediaEditAdjustments> adjustments, UIImage *resultImage, UIImage *thumbnailImage, bool hasChanges, void(^commit)(void));

@property (nonatomic, assign) bool skipInitialTransition;
@property (nonatomic, assign) bool dontHideStatusBar;
@property (nonatomic, strong) PGCameraShotMetadata *metadata;
@property (nonatomic, strong) NSArray *faces;

@property (nonatomic, strong) NSString *senderName;

@property (nonatomic, strong) AVPlayer *player;

@property (nonatomic, strong) UIView<TGPhotoDrawingEntitiesView> *entitiesView;

@property (nonatomic, assign) bool ignoreCropForResult;

- (instancetype)initWithContext:(id<LegacyComponentsContext>)context item:(id<TGMediaEditableItem>)item intent:(TGPhotoEditorControllerIntent)intent adjustments:(id<TGMediaEditAdjustments>)adjustments caption:(NSAttributedString *)caption screenImage:(UIImage *)screenImage availableTabs:(TGPhotoEditorTab)availableTabs selectedTab:(TGPhotoEditorTab)selectedTab;

- (void)dismissEditor;
- (void)applyEditor;

- (void)setInfoString:(NSString *)string;

- (void)dismissAnimated:(bool)animated;

- (void)updateStatusBarAppearanceForDismiss;
- (CGSize)referenceViewSize;

- (void)_setScreenImage:(UIImage *)screenImage;
- (void)_finishedTransitionIn;
- (UIView *)transitionWrapperView;
- (CGFloat)toolbarLandscapeSize;

- (void)setToolbarHidden:(bool)hidden animated:(bool)animated;

+ (TGPhotoEditorTab)defaultTabsForAvatarIntent:(bool)hasStickers;

- (NSTimeInterval)currentTime;
- (void)setMinimalVideoDuration:(NSTimeInterval)duration;

@end

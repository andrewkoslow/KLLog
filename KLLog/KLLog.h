//
//  KLLog.h
//  KLLog
//
//  Created by Andrew Koslow on 13.06.12.
//  Copyright (c) 2012 Andrew Koslow. All rights reserved.
//


#pragma mark - Customizable Definitions

#ifndef KL_LOG_ENABLE
#define KL_LOG_ENABLE 1
#endif


#ifndef ____KLLog
#define ____KLLog(level, message) NSLog(@"%@ %@", ____KLLogLevelString(level), message)
#endif


#pragma mark - Constants

#define KL_LOG_LEVEL_EMERG      0
#define KL_LOG_LEVEL_ALERT      1
#define KL_LOG_LEVEL_CRIT       2
#define KL_LOG_LEVEL_ERRR       3
#define KL_LOG_LEVEL_WARN       4
#define KL_LOG_LEVEL_NOTE       5
#define KL_LOG_LEVEL_INFO       6
#define KL_LOG_LEVEL_DEBUG      7


#pragma mark - Conventional Shorthands

#define KLLog(variables...)         KLInform(variables)
#define KLLogM(message)             KLInformM(message)
#define KLLogV(variables...)        KLInformV(variables)
#define KLLogS()                    KLInformS()
#define KLLogSM(message)            KLInformSM(message)
#define KLLogSV(variables...)       KLInformSV(variables)

#define KLInform(variables...)      KLInformSV(variables)
#define KLInformM(message)          KLLogMes(KL_LOG_ENABLE, KL_LOG_LEVEL_DEBUG, message)
#define KLInformV(variables...)     KLLogVars(KL_LOG_ENABLE, KL_LOG_LEVEL_DEBUG, variables)
#define KLInformS()                 KLLogSel(KL_LOG_ENABLE, KL_LOG_LEVEL_DEBUG)
#define KLInformSM(message)         KLLogSelMes(KL_LOG_ENABLE, KL_LOG_LEVEL_DEBUG, message)
#define KLInformSV(variables...)    KLLogSelVars(KL_LOG_ENABLE, KL_LOG_LEVEL_DEBUG, variables)

#define KLWarn(variables...)        KLWarnSV(variables)
#define KLWarnM(message)            KLLogMes(KL_LOG_ENABLE, KL_LOG_LEVEL_WARN, message)
#define KLWarnV(variables...)       KLLogVars(KL_LOG_ENABLE, KL_LOG_LEVEL_WARN, variables)
#define KLWarnS()                   KLLogSel(KL_LOG_ENABLE, KL_LOG_LEVEL_WARN)
#define KLWarnSM(message)           KLLogSelMes(KL_LOG_ENABLE, KL_LOG_LEVEL_WARN, message)
#define KLWarnSV(variables...)      KLLogSelVars(KL_LOG_ENABLE, KL_LOG_LEVEL_WARN, variables)

#define KLPanic(variables...)       KLPanicSV(variables)
#define KLPanicM(message)           KLLogMes(KL_LOG_ENABLE, KL_LOG_LEVEL_EMERG, message)
#define KLPanicV(variables...)      KLLogVars(KL_LOG_ENABLE, KL_LOG_LEVEL_EMERG, variables)
#define KLPanicS()                  KLLogSel(KL_LOG_ENABLE, KL_LOG_LEVEL_EMERG)
#define KLPanicSM(message)          KLLogSelMes(KL_LOG_ENABLE, KL_LOG_LEVEL_EMERG, message)
#define KLPanicSV(variables...)     KLLogSelVars(KL_LOG_ENABLE, KL_LOG_LEVEL_EMERG, variables)


#pragma mark - Base Macros

#define KLLogMes(boundary, level, message) ____KLLogBoundaryWrapper(boundary, ____KLLog, level, message)
#define KLLogVars(boundary, level, variables...) ____KLLogBoundaryWrapper(boundary, ____KLLogVars, level, ____KLLogArgCount(variables), variables)
#define KLLogSel(boundary, level) ____KLLogBoundaryWrapper(boundary, ____KLLogSel, level)
#define KLLogSelMes(boundary, level, message) ____KLLogBoundaryWrapper(boundary, ____KLLogSelMes, level, message)
#define KLLogSelVars(boundary, level, variables...) ____KLLogBoundaryWrapper(boundary, ____KLLogSelVars, level, ____KLLogArgCount(variables), variables)


#pragma mark - Implementation

#define ____KLLogVars(____level, ARG_COUNT, ...) {\
    ____KLLog(____level, ([[NSArray arrayWithObjects:____KLLogVal ## ARG_COUNT(__VA_ARGS__), nil] componentsJoinedByString:@", "]));\
}

#define ____KLLogSel(____level) {\
    ____KLLog(____level, (____KLLogString(@"%s", __PRETTY_FUNCTION__)));\
}

#define ____KLLogSelMes(____level, ____message) {\
    ____KLLog(____level, (____KLLogString(@"%s --- %@", __PRETTY_FUNCTION__, ____message)));\
}

#define ____KLLogSelVars(____level, ARG_COUNT, ...) {\
    ____KLLog(____level, (____KLLogString(@"%s --- %@", __PRETTY_FUNCTION__, [[NSArray arrayWithObjects:____KLLogVal ## ARG_COUNT(__VA_ARGS__), nil] componentsJoinedByString:@", "])));\
}

#define ____KLLogBoundaryWrapper(____boundary, ____macro, ...) if (____boundary) do { ____macro(__VA_ARGS__); } while (0)

#define ____KLLogLevelString(level)\
(((level) == KL_LOG_LEVEL_EMERG) ?  @"<Emergency>"  :\
(((level) == KL_LOG_LEVEL_ALERT) ?  @"<Alert>"      :\
(((level) == KL_LOG_LEVEL_CRIT) ?   @"<Critical>"   :\
(((level) == KL_LOG_LEVEL_ERRR) ?   @"<Error>"      :\
(((level) == KL_LOG_LEVEL_WARN) ?   @"<Warning>"    :\
(((level) == KL_LOG_LEVEL_NOTE) ?   @"<Notice>"     :\
(((level) == KL_LOG_LEVEL_INFO) ?   @"<Info>"       :\
@"<Debug>")))))))


#define ____KLLogArgCount(...) ____KLLogArgCountImpl(__VA_ARGS__, 8, 7, 6, 5, 4, 3, 2, 1)
#define ____KLLogArgCountImpl(_1,_2,_3,_4,_5,_6,_7,_8,N,...) N

#define ____KLLogVal8(v1, ...) ____KLLogVal(v1), ____KLLogVal7(__VA_ARGS__)
#define ____KLLogVal7(v1, ...) ____KLLogVal(v1), ____KLLogVal6(__VA_ARGS__)
#define ____KLLogVal6(v1, ...) ____KLLogVal(v1), ____KLLogVal5(__VA_ARGS__)
#define ____KLLogVal5(v1, ...) ____KLLogVal(v1), ____KLLogVal4(__VA_ARGS__)
#define ____KLLogVal4(v1, ...) ____KLLogVal(v1), ____KLLogVal3(__VA_ARGS__)
#define ____KLLogVal3(v1, ...) ____KLLogVal(v1), ____KLLogVal2(__VA_ARGS__)
#define ____KLLogVal2(v1, ...) ____KLLogVal(v1), ____KLLogVal1(__VA_ARGS__)
#define ____KLLogVal1(v1) ____KLLogVal(v1)

#define ____KLLogExprByType(v, t, e1, e2) __builtin_choose_expr(__builtin_types_compatible_p(__typeof(v), t), e1, e2)
#define ____KLLogExprByTypeEval(...) ____KLLogExprByType(__VA_ARGS__)

#define ____KLLogValByType(v, t, d) __builtin_choose_expr(__builtin_types_compatible_p(__typeof(v), t), v, (t)d)
#define ____KLLogValByTypeEval(...) ____KLLogValByType(__VA_ARGS__)

#define ____KLLogString(...) [NSString stringWithFormat:__VA_ARGS__]

#define ____KLLogStringByType(v, t, f, x1, d, n) ____KLLogExprByTypeEval(v, t, (____KLLogString(@"%s " # f, #v, x1 (____KLLogValByTypeEval(v, t, d)))), n)
#define ____KLLogStringByTypeEval(...) ____KLLogStringByType(__VA_ARGS__)

#define ____KLLogNSStringFromBOOL(b) (b ? @"YES" : @"NO")

#define ____KLLogVal(v)\
____KLLogStringByTypeEval(v, id,                        %@,   ,                           nil,\
____KLLogStringByTypeEval(v, SEL,                       %@,   NSStringFromSelector,       nil,\
____KLLogStringByTypeEval(v, CGSize,                    %@,   NSStringFromCGSize,         CGSizeZero,\
____KLLogStringByTypeEval(v, CGPoint,                   %@,   NSStringFromCGPoint,        CGPointZero,\
____KLLogStringByTypeEval(v, CGRect,                    %@,   NSStringFromCGRect,         CGRectZero,\
____KLLogStringByTypeEval(v, NSRange,                   %@,   NSStringFromRange,          NSMakeRange(0, 0),\
____KLLogStringByTypeEval(v, UIEdgeInsets,              %@,   NSStringFromUIEdgeInsets,   UIEdgeInsetsZero,\
____KLLogStringByTypeEval(v, CFIndex,                   %ld,  ,                           0,\
____KLLogStringByTypeEval(v, CGFloat,                   %f,   ,                           0,\
____KLLogStringByTypeEval(v, signed short int,          %hd,  ,                           0,\
____KLLogStringByTypeEval(v, unsigned short int,        %hd,  ,                           0,\
____KLLogStringByTypeEval(v, BOOL,                      %@,   ____KLLogNSStringFromBOOL,  NO,\
____KLLogStringByTypeEval(v, char,                      %c,   ,                           0,\
____KLLogStringByTypeEval(v, signed char,               %c,   ,                           0,\
____KLLogStringByTypeEval(v, unsigned char,             %c,   ,                           0,\
____KLLogStringByTypeEval(v, int,                       %d,   ,                           0,\
____KLLogStringByTypeEval(v, uint,                      %u,   ,                           0,\
____KLLogStringByTypeEval(v, unsigned int,              %u,   ,                           0,\
____KLLogStringByTypeEval(v, long int,                  %ld,  ,                           0,\
____KLLogStringByTypeEval(v, unsigned long int,         %lu,  ,                           0,\
____KLLogStringByTypeEval(v, long long int,             %lld, ,                           0,\
____KLLogStringByTypeEval(v, unsigned long long int,    %llu, ,                           0,\
____KLLogStringByTypeEval(v, float,                     %f,   ,                           0,\
____KLLogStringByTypeEval(v, double,                    %f,   ,                           0,\
____KLLogStringByTypeEval(v, long double,               %Lf,  ,                           0,\
____KLLogStringByTypeEval(v, void *,                    %p,   ,                           NULL,\
(____KLLogString(@"%s %@", #v, @"<Unknown Type>"))))))))))))))))))))))))))))


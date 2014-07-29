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

#define KLLog(variables...)         KLLogSV(variables)
#define KLLogM(message)             KLLogMes(KL_LOG_ENABLE, KL_LOG_LEVEL_DEBUG, message)
#define KLLogV(variables...)        KLLogVars(KL_LOG_ENABLE, KL_LOG_LEVEL_DEBUG, variables)
#define KLLogP(pairs...)            KLLogPairs(KL_LOG_ENABLE, KL_LOG_LEVEL_DEBUG, pairs)
#define KLLogS()                    KLLogSel(KL_LOG_ENABLE, KL_LOG_LEVEL_DEBUG)
#define KLLogSM(message)            KLLogSelMes(KL_LOG_ENABLE, KL_LOG_LEVEL_DEBUG, message)
#define KLLogSV(variables...)       KLLogSelVars(KL_LOG_ENABLE, KL_LOG_LEVEL_DEBUG, variables)

#define KLInform(variables...)      KLInformSV(variables)
#define KLInformM(message)          KLLogMes(KL_LOG_ENABLE, KL_LOG_LEVEL_INFO, message)
#define KLInformV(variables...)     KLLogVars(KL_LOG_ENABLE, KL_LOG_LEVEL_INFO, variables)
#define KLInformP(pairs...)         KLLogPairs(KL_LOG_ENABLE, KL_LOG_LEVEL_INFO, pairs)
#define KLInformS()                 KLLogSel(KL_LOG_ENABLE, KL_LOG_LEVEL_INFO)
#define KLInformSM(message)         KLLogSelMes(KL_LOG_ENABLE, KL_LOG_LEVEL_INFO, message)
#define KLInformSV(variables...)    KLLogSelVars(KL_LOG_ENABLE, KL_LOG_LEVEL_INFO, variables)

#define KLWarn(variables...)        KLWarnSV(variables)
#define KLWarnM(message)            KLLogMes(KL_LOG_ENABLE, KL_LOG_LEVEL_WARN, message)
#define KLWarnV(variables...)       KLLogVars(KL_LOG_ENABLE, KL_LOG_LEVEL_WARN, variables)
#define KLWarnP(pairs...)           KLLogPairs(KL_LOG_ENABLE, KL_LOG_LEVEL_WARN, pairs)
#define KLWarnS()                   KLLogSel(KL_LOG_ENABLE, KL_LOG_LEVEL_WARN)
#define KLWarnSM(message)           KLLogSelMes(KL_LOG_ENABLE, KL_LOG_LEVEL_WARN, message)
#define KLWarnSV(variables...)      KLLogSelVars(KL_LOG_ENABLE, KL_LOG_LEVEL_WARN, variables)

#define KLPanic(variables...)       KLPanicSV(variables)
#define KLPanicM(message)           KLLogMes(KL_LOG_ENABLE, KL_LOG_LEVEL_EMERG, message)
#define KLPanicV(variables...)      KLLogVars(KL_LOG_ENABLE, KL_LOG_LEVEL_EMERG, variables)
#define KLPanicP(pairs...)          KLLogPairs(KL_LOG_ENABLE, KL_LOG_LEVEL_EMERG, pairs)
#define KLPanicS()                  KLLogSel(KL_LOG_ENABLE, KL_LOG_LEVEL_EMERG)
#define KLPanicSM(message)          KLLogSelMes(KL_LOG_ENABLE, KL_LOG_LEVEL_EMERG, message)
#define KLPanicSV(variables...)     KLLogSelVars(KL_LOG_ENABLE, KL_LOG_LEVEL_EMERG, variables)


#pragma mark - Base Macros

#define KLLogMes(boundary, level, message) ____KLLogBoundaryWrapper(boundary, ____KLLog, level, message)
#define KLLogVars(boundary, level, variables...) ____KLLogBoundaryWrapper(boundary, ____KLLogVars, level, ____KLLogArgCount(variables), variables)
#define KLLogPairs(boundary, level, pairs...) ____KLLogBoundaryWrapper(boundary, ____KLLogPairs, level, ____KLLogArgCount(pairs), pairs)
#define KLLogSel(boundary, level) ____KLLogBoundaryWrapper(boundary, ____KLLogSel, level)
#define KLLogSelMes(boundary, level, message) ____KLLogBoundaryWrapper(boundary, ____KLLogSelMes, level, message)
#define KLLogSelVars(boundary, level, variables...) ____KLLogBoundaryWrapper(boundary, ____KLLogSelVars, level, ____KLLogArgCount(variables), variables)


#pragma mark - Implementation

#define ____KLLogVars(____level, ARG_COUNT, ...) {\
    ____KLLog(____level, ([[NSArray arrayWithObjects:____KLLogVal ## ARG_COUNT(__VA_ARGS__), nil] componentsJoinedByString:@", "]));\
}

#define ____KLLogPairs(____level, ARG_COUNT, ...) {\
____KLLog(____level, ([[NSArray arrayWithObjects:____KLLogPair ## ARG_COUNT(__VA_ARGS__), nil] componentsJoinedByString:@""]));\
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


#define ____KLLogArgCount(...) ____KLLogArgCountImpl(__VA_ARGS__, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
#define ____KLLogArgCountImpl(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,N,...) N

#define ____KLLogVal16(v, ...)      ____KLLogVal(#v " ", v), ____KLLogVal15(__VA_ARGS__)
#define ____KLLogVal15(v, ...)      ____KLLogVal(#v " ", v), ____KLLogVal14(__VA_ARGS__)
#define ____KLLogVal14(v, ...)      ____KLLogVal(#v " ", v), ____KLLogVal13(__VA_ARGS__)
#define ____KLLogVal13(v, ...)      ____KLLogVal(#v " ", v), ____KLLogVal12(__VA_ARGS__)
#define ____KLLogVal12(v, ...)      ____KLLogVal(#v " ", v), ____KLLogVal11(__VA_ARGS__)
#define ____KLLogVal11(v, ...)      ____KLLogVal(#v " ", v), ____KLLogVal10(__VA_ARGS__)
#define ____KLLogVal10(v, ...)      ____KLLogVal(#v " ", v), ____KLLogVal9(__VA_ARGS__)
#define ____KLLogVal9(v, ...)       ____KLLogVal(#v " ", v), ____KLLogVal8(__VA_ARGS__)
#define ____KLLogVal8(v, ...)       ____KLLogVal(#v " ", v), ____KLLogVal7(__VA_ARGS__)
#define ____KLLogVal7(v, ...)       ____KLLogVal(#v " ", v), ____KLLogVal6(__VA_ARGS__)
#define ____KLLogVal6(v, ...)       ____KLLogVal(#v " ", v), ____KLLogVal5(__VA_ARGS__)
#define ____KLLogVal5(v, ...)       ____KLLogVal(#v " ", v), ____KLLogVal4(__VA_ARGS__)
#define ____KLLogVal4(v, ...)       ____KLLogVal(#v " ", v), ____KLLogVal3(__VA_ARGS__)
#define ____KLLogVal3(v, ...)       ____KLLogVal(#v " ", v), ____KLLogVal2(__VA_ARGS__)
#define ____KLLogVal2(v, ...)       ____KLLogVal(#v " ", v), ____KLLogVal1(__VA_ARGS__)
#define ____KLLogVal1(v)            ____KLLogVal(#v " ", v)

#define ____KLLogPair16(m, v, ...)  ____KLLogPair2(m, v), ____KLLogPair14(__VA_ARGS__)
#define ____KLLogPair14(m, v, ...)  ____KLLogPair2(m, v), ____KLLogPair12(__VA_ARGS__)
#define ____KLLogPair12(m, v, ...)  ____KLLogPair2(m, v), ____KLLogPair10(__VA_ARGS__)
#define ____KLLogPair10(m, v, ...)  ____KLLogPair2(m, v), ____KLLogPair8(__VA_ARGS__)
#define ____KLLogPair8(m, v, ...)   ____KLLogPair2(m, v), ____KLLogPair6(__VA_ARGS__)
#define ____KLLogPair6(m, v, ...)   ____KLLogPair2(m, v), ____KLLogPair4(__VA_ARGS__)
#define ____KLLogPair4(m, v, ...)   ____KLLogPair2(m, v), ____KLLogPair2(__VA_ARGS__)
#define ____KLLogPair2(m, v) m,     ____KLLogVal(, v)

#define ____KLLogExprByType(v, t, e1, e2) __builtin_choose_expr(__builtin_types_compatible_p(__typeof(v), t), e1, e2)
#define ____KLLogExprByTypeEval(...) ____KLLogExprByType(__VA_ARGS__)

#define ____KLLogValByType(v, t, d) __builtin_choose_expr(__builtin_types_compatible_p(__typeof(v), t), (__typeof(v))v, (t)d)
#define ____KLLogValByTypeEval(...) ____KLLogValByType(__VA_ARGS__)

#define ____KLLogString(...) [NSString stringWithFormat:__VA_ARGS__]

#define ____KLLogStringByType(n, v, t, f2, x1, d, x2) ____KLLogExprByTypeEval(v, t, (____KLLogString(@ n #f2, x1 (____KLLogValByTypeEval(v, t, d)))), x2)
#define ____KLLogStringByTypeEval(...) ____KLLogStringByType(__VA_ARGS__)

#define ____KLLogNSStringFromBOOL(b) (b ? @"YES" : @"NO")

#define ____KLLogVal(n, v)\
____KLLogStringByTypeEval(n, v, id,                        %@,   ,                           nil,\
____KLLogStringByTypeEval(n, v, SEL,                       %@,   NSStringFromSelector,       nil,\
____KLLogStringByTypeEval(n, v, CGSize,                    %@,   NSStringFromCGSize,         CGSizeZero,\
____KLLogStringByTypeEval(n, v, CGPoint,                   %@,   NSStringFromCGPoint,        CGPointZero,\
____KLLogStringByTypeEval(n, v, CGRect,                    %@,   NSStringFromCGRect,         CGRectZero,\
____KLLogStringByTypeEval(n, v, NSRange,                   %@,   NSStringFromRange,          NSMakeRange(0, 0),\
____KLLogStringByTypeEval(n, v, UIEdgeInsets,              %@,   NSStringFromUIEdgeInsets,   UIEdgeInsetsZero,\
____KLLogStringByTypeEval(n, v, CFIndex,                   %ld,  ,                           0,\
____KLLogStringByTypeEval(n, v, CGFloat,                   %f,   ,                           0,\
____KLLogStringByTypeEval(n, v, signed short int,          %hd,  ,                           0,\
____KLLogStringByTypeEval(n, v, unsigned short int,        %hd,  ,                           0,\
____KLLogStringByTypeEval(n, v, BOOL,                      %@,   ____KLLogNSStringFromBOOL,  NO,\
____KLLogStringByTypeEval(n, v, char,                      %c,   ,                           0,\
____KLLogStringByTypeEval(n, v, signed char,               %c,   ,                           0,\
____KLLogStringByTypeEval(n, v, unsigned char,             %c,   ,                           0,\
____KLLogStringByTypeEval(n, v, int,                       %d,   ,                           0,\
____KLLogStringByTypeEval(n, v, uint,                      %u,   ,                           0,\
____KLLogStringByTypeEval(n, v, unsigned int,              %u,   ,                           0,\
____KLLogStringByTypeEval(n, v, long int,                  %ld,  ,                           0,\
____KLLogStringByTypeEval(n, v, unsigned long int,         %lu,  ,                           0,\
____KLLogStringByTypeEval(n, v, long long int,             %lld, ,                           0,\
____KLLogStringByTypeEval(n, v, unsigned long long int,    %llu, ,                           0,\
____KLLogStringByTypeEval(n, v, float,                     %f,   ,                           0,\
____KLLogStringByTypeEval(n, v, double,                    %f,   ,                           0,\
____KLLogStringByTypeEval(n, v, long double,               %Lf,  ,                           0,\
____KLLogStringByTypeEval(n, v, void *,                    %p,   ,                           NULL,\
(____KLLogString(@"%s %@", #v, @"<Unknown Type>"))))))))))))))))))))))))))))


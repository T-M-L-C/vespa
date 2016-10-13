// Copyright 2016 Yahoo Inc. Licensed under the terms of the Apache 2.0 license. See LICENSE in the project root.

#include <vespa/fastos/fastos.h>
#include <vespa/log/log.h>
LOG_SETUP(".engine.searchreply");
#include "searchreply.h"
#include <vespa/searchlib/common/mapnames.h>

namespace search {
namespace engine {

SearchReply::SearchReply()
    : valid(true),
      offset(0),
      _distributionKey(0),
      totalHitCount(0),
      maxRank(0),
      sortIndex(),
      sortData(),
      groupResult(),
      coverage(),
      useWideHits(false),
      hits(),
      errorCode(0),
      errorMessage(),
      useQueueLen(false),
      queueLen(0),
      request()
{
}

SearchReply::SearchReply(const SearchReply &rhs)
    :
    valid        (rhs.valid),
    offset       (rhs.offset),
    _distributionKey     (rhs._distributionKey),
    totalHitCount(rhs.totalHitCount),
    maxRank      (rhs.maxRank),
    sortIndex    (rhs.sortIndex),
    sortData     (rhs.sortData),
    groupResult  (rhs.groupResult),
    coverage     (rhs.coverage),
    useWideHits  (rhs.useWideHits),
    hits         (rhs.hits),
    errorCode    (rhs.errorCode),
    errorMessage (rhs.errorMessage),
    useQueueLen  (rhs.useQueueLen),
    queueLen     (rhs.queueLen),
    request() // NB not copied
{
}

} // namespace engine
} // namespace search

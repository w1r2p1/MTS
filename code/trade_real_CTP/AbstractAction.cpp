
/*****************************************************************************
* Copyright [2017-2019] [MTSQuant]
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*  http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*****************************************************************************/
#include "AbstractAction.h"
#include "ctp_ext/CTPUtils.h"
#include "base/MtsUtils.h"

AbstractAction::AbstractAction()
{
}


AbstractAction::~AbstractAction() {
}

int AbstractAction::request(CThostFtdcTraderApi* userApi, int requestId) {
    _reqId = requestId;
    return doRequest(userApi,requestId);
}

int AbstractAction::requestId() const {
    return _reqId;
}


void AbstractAction::emitActionError(CThostFtdcRspInfoField * pRspInfo, OwnerLevel ol) {
    if (pRspInfo == nullptr) {
		Q_EMIT actionError(-1, "Unknown Error",ol);
    } else {
		Q_EMIT actionError(pRspInfo->ErrorID, MtsUtils::toUtf8(pRspInfo->ErrorMsg), ol);
    }
}

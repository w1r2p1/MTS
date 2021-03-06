
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
#include "FeedsReal.h"
#include "mts_core/ConfigParams.h"
#ifndef NDEBUG
#include "mts_core/Environment.h"
#endif
#include "QuoteEvent.h"

namespace mts
{

	FeedsReal::FeedsReal()
		:Feeds() , _feedsClient(nullptr)
	{
		this->setObjectName("FeedsRealCTP");
		EventDispatcher::defaultDispatcher()->addCallback(this);
	}


	FeedsReal::~FeedsReal() {
		EventDispatcher::defaultDispatcher()->removeCallback(this);
		delete _feedsClient;
		_feedsClient = nullptr;
	}

	bool FeedsReal::initialize(const QVariantMap & params) {
		assert(ConfigParams::isInitialized());
		auto feedsFront = ConfigParams::instance()->feedsFront("CTP");
		auto userName = feedsFront.userName();
		auto password = feedsFront.password();
		MTS_DEBUG ( "Login Feeds as '%s'\n" , qPrintable ( userName ) );
		_feedsClient = new CTPFeedsClient(feedsFront.clearUserPassword()/*should not contains user and password*/,
															ConfigParams::instance()->brokerId("CTP"),
															userName,
															password
															);
		connect(_feedsClient, SIGNAL(loginDone()), this, SLOT(emitInitializeDone()));
		connect(_feedsClient, SIGNAL(loginError(const QString&)), this, SLOT(emitInitializeError(const QString&)));
		return _feedsClient->connectFront();
	}


	int FeedsReal::subscribe(const QList<mts::InstrumentId> & instruments ) {
		assert(_feedsClient);
		_feedsClient->setSubscribeInstruments(instruments);
		return _feedsClient->subscribe();
	}

	int FeedsReal::unsubscribe(const QList<InstrumentId> &) {
		return 0;
	}


	void FeedsReal::onEvent(const EventPtr &evt) {
		assert(Environment::instance()->isCurrentMtsThread());
		if (evt->type() == EVT_QUOTE) {
			auto quoteEvt=qSharedPointerDynamicCast<QuoteEvent>(evt);
			this->notifyAll(quoteEvt->data());
		}
	}


	

}
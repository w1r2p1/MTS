
/*****************************************************************************
* Copyright [2018-2019] [3fellows]
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
#pragma once
#include <QtCore/QObject>
#include "mts_core/InstrumentId.h"
#include "mts_core/QuoteSet.h"
#include "mts_core/StrategyInterface.h"

namespace mts
{
	class QuoteMgr :public QObject,public FeedsCallback
	{
		Q_OBJECT;
		QuoteMgr();
		virtual ~QuoteMgr();
	public:
		static QuoteMgr* instance();
		void setStrategy(StrategyInterface* notify);
	public Q_SLOTS:
		int subscribe(const QList<InstrumentId>&);
		int unsubscribe(const QList<InstrumentId>&);
		Quote* getQuote(const InstrumentId&);

		int subscribedInstrumentCount() const;
		// 通过 FeedsCallback 继承
		virtual void onQuoteUpdate(QuotePtr) override;
		virtual void onBusinessDateChanged(int businessDate) override;
		// 通过 FeedsCallback 继承
		virtual void onBarUpdate(CalcBarPtr) override;
	private:
		QuoteSet  _quoteSet;
		StrategyInterface* _notify;

	};
}
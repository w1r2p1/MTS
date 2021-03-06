
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
#pragma once

#include "AbstractConfigParams.h"

namespace mts
{

	class MTS_CORE_API SysConfigParams :public AbstractConfigParams
	{
	protected:
		SysConfigParams();
		virtual ~SysConfigParams();

		virtual bool doLoad(const QVariantMap & params) override;
	public:

		QString configDir() const;
		QString docDir() const;
		QString mtsDir() const;

		QString logFile() const;
		QString continuousContractFile() const;
		QString instrumentDbFile() const;
		QString riskSettingFile() const;


		QString logDir() const;
	private:
		QString _configDir;
		QString _docDir;
		QString _mtsDir;

		QString _logFile;
		QString _continuousContractFile;
		QString _riskSettingFile;
	};

}


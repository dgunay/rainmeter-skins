[Variables]
WeatherIconNames="47":"storm", "46":"snow", "45":"rain", "44":"partly_cloudy_day", "43":"snow", "42":"snow", "41":"snow", "40":"rain", "39":"rain", "38":"storm", "37":"thunder", "36":"clear_day", "35":"sleet", "34":"partly_cloudy_day", "33":"partly_cloudy_night", "32":"clear_day", "31":"clear_night", "30":"partly_cloudy_day", "29":"partly_cloudy_night", "28":"mostly_cloudy_day", "27":"mostly_cloudy_night", "26":"cloudy", "25":"cloudy", "24":"windy", "23":"windy", "22":"fog", "21":"fog", "20":"fog", "19":"fog", "18":"sleet", "17":"sleet", "16":"snow", "15":"snow", "14":"snow", "13":"snow", "12":"rain", "11":"rain", "10":"sleet", "9":"rain", "8":"sleet", "7":"sleet", "6":"sleet", "5":"sleet", "4":"storm", "3":"storm", "2":"storm", "1":"storm", "0":"storm", "":"unknown"

;================================================

[MeasureSystemLocale]
Measure=Registry

RegHKey=HKEY_CURRENT_USER
RegKey=Control Panel\International
RegValue=LocaleName

Substitute="(\w+)(-\w+)?":"\1"
RegExpSubstitute=1

[MeasureWeatherLocationCode]
Measure=WebParser

URL=http://wxdata.weather.com/wxdata/search/search?where=#WeatherLocation#
RegExp=(?siU)<loc id="(.*)" type=".*">(.*)</loc>
StringIndex=1
UpdateRate=-1

FinishAction=[!Log "Selected weather location is: [MeasureWeatherLocation]." Notice] [!EnableMeasureGroup Weather] [!UpdateMeasureGroup Weather]
OnConnectErrorAction=[!Log "Couldn't connect to weather.com" Error]
OnRegExpErrorAction=[!Log "Couldn't get location code." Error]

[MeasureWeatherLocation]
Measure=WebParser
URL=[MeasureWeatherLocationCode]
StringIndex=2

Substitute="":"N/A"

;================================================

[MeasureWeather]
Group=Weather
Measure=WebParser

URL=http://wxdata.weather.com/wxdata/weather/local/[&MeasureWeatherLocationCode]?cc=*&unit=#WeatherUnit#&locale=[&MeasureSystemLocale]
RegExp=(?siU)<tmp>(.*)</tmp>.*<t>(.*)</t>.*<icon>(.*)</icon>
UpdateRate=(60*5)

Disabled=1
DynamicVariables=1

FinishAction=[!Log "Finished downloading weather info." Notice] [!UpdateMeterGroup Weather] [!UpdateMeterGroup Weather] [!Redraw]
OnConnectErrorAction=[!Log "Couldn't connect to weather.com" Error]
OnRegExpErrorAction=[!Log "Couldn't parse weather info." Error]

;================================================

[MeasureWeatherTemperature]
Measure=WebParser
URL=[MeasureWeather]
StringIndex=1

Substitute="":"N/A"

[MeasureWeatherConditionName]
Measure=WebParser
URL=[MeasureWeather]
StringIndex=2

Substitute="":"N/A"

[MeasureWeatherConditionCode]
Measure=WebParser
URL=[MeasureWeather]
StringIndex=3

Substitute="#WeatherIconNames#"

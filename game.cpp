#include "node.h"
#include "v8.h"


namespace algorithm {
	const std::vector<std::vector<int>> align = { { 0,1,2 },{ 3,4,5 },{ 6,7,8 },{ 0,3,6 },{ 1,4,7 },{ 2,5,8 },{ 0,4,8 },{ 2,4,6 } };// series of three numbers that are aligned
	
	char allSame(char one, char two, char three) { //returns value if all three have the same value
		if (one == two && two == three && one != ' ') {
			return one;
		}
		else {
			return ' ';
		}
	}

	char whoWin(const char gameArray[9]) {// checks who wins
		if (allSame(gameArray[0], gameArray[1], gameArray[2]) != ' ') return gameArray[0];//horizontal
		else if (allSame(gameArray[3], gameArray[4], gameArray[5]) != ' ') return gameArray[3];
		else if (allSame(gameArray[6], gameArray[7], gameArray[8]) != ' ') return gameArray[6];
		else if (allSame(gameArray[0], gameArray[3], gameArray[6]) != ' ') return gameArray[0];//vertical
		else if (allSame(gameArray[1], gameArray[4], gameArray[7]) != ' ') return gameArray[1];
		else if (allSame(gameArray[2], gameArray[5], gameArray[8]) != ' ') return gameArray[2];
		else if (allSame(gameArray[0], gameArray[4], gameArray[8]) != ' ') return gameArray[0];//diagonal
		else if (allSame(gameArray[2], gameArray[4], gameArray[6]) != ' ') return gameArray[2];//diagonal
		else return ' ';
	}

	bool include(char x, int one, int two, int three) {
		if (one == x || two == x || three == x) {
			return true;
		}
		else return false;
	}

	bool onlyTwo(char x, char one, char two, char three) {// returns true only if there is only one number of the three that is equal to x
		int amount = 0;

		if (one == x) amount++;
		else if (one != ' ') return false;
		if (two == x) amount++;
		else if (two != ' ') return false;
		if (three == x) amount++;
		else if (three != ' ') return false;

		if (amount == 2) return true;
		else return false;
	}

	//all functions below until getCoordinates() are for CPU's turn
	std::vector<int> filterPlaced(std::vector<int> arrayValues, const char gameArray[9]) { // filters out locations already placed
		std::vector<int> localArrayValues = arrayValues;

		for (int repeat = 0; repeat < 9; repeat++) {
			if (gameArray[repeat] != ' ') {
				localArrayValues[repeat] = -1;
			}
		}
		return localArrayValues;
	}

	std::vector<int> open(const char gameArray[9], char who) {
		std::vector<int> arrayValues = { 0,0,0,0,0,0,0,0,0 };
			
			for (int repeat = 0; repeat < 8; repeat++) {
				if (include(who, align[repeat][0], align[repeat][1], align[repeat][2]) == false) {
					arrayValues[align[repeat][0]] += 1;
					arrayValues[align[repeat][1]] += 1;
					arrayValues[align[repeat][2]] += 1;
				}
			}

		return arrayValues;
	}

	std::vector<int> instantDanger(const char myArray[9]) {// detects if computer is in instant danger
		std::vector<int> arrayValues = { 0,0,0,0,0,0,0,0,0 };

		
		bool self = false;
		bool enemy = false;

		for (int repeat = 0; repeat < 8; repeat++) {
			if (onlyTwo('X', myArray[align[repeat][0]], myArray[align[repeat][1]], myArray[align[repeat][2]]) == true) enemy = true;
			if (onlyTwo('O', myArray[align[repeat][0]], myArray[align[repeat][1]], myArray[align[repeat][2]]) == true) self = true;
		}

		for (int repeat = 0; repeat < 8; repeat++) {
			if (onlyTwo('X', myArray[align[repeat][0]], myArray[align[repeat][1]], myArray[align[repeat][2]]) == true && self == false) {
				arrayValues[align[repeat][0]] += 10;
				arrayValues[align[repeat][1]] += 10;
				arrayValues[align[repeat][2]] += 10;
			}
			else if (onlyTwo('O', myArray[align[repeat][0]], myArray[align[repeat][1]], myArray[align[repeat][2]]) == true) {
				arrayValues[align[repeat][0]] += 10;
				arrayValues[align[repeat][1]] += 10;
				arrayValues[align[repeat][2]] += 10;
			}
		}
		return arrayValues;
	}

	std::vector<int> lookAheadCase(const char gameArray[9]) {
		std::vector<int> arrayValues = { 0,0,0,0,0,0,0,0,0 };
		if (gameArray[0] == 'X' && gameArray[1] == ' ' && gameArray[2] == ' ' &&
			gameArray[3] == ' ' && gameArray[4] == 'O' && gameArray[5] == ' ' &&
			gameArray[6] == ' ' && gameArray[7] == ' ' && gameArray[8] == 'X') return { 0,20,0,0,0,0,0,0,0 };
		else if (gameArray[0] == ' ' && gameArray[1] == ' ' && gameArray[2] == 'X' &&
			gameArray[3] == ' ' && gameArray[4] == 'O' && gameArray[5] == ' ' &&
			gameArray[6] == 'X' && gameArray[7] == ' ' && gameArray[8] == ' ') return { 0,20,0,0,0,0,0,0,0 };
		else return arrayValues;
	}

	int cpuTurn(const char gameArray[9], bool debug) {// returns coordinate where cpu should go on his turn
		std::vector<int> arrayValues = { 0,0,0,0,0,0,0,0,0 };

		for (int sumUp = 0; sumUp < 9; sumUp++) {// sum up open(gameArray) and possible(gameArray)
			arrayValues[sumUp] = open(gameArray, 'X')[sumUp] + open(gameArray, 'O')[sumUp] + instantDanger(gameArray)[sumUp] + lookAheadCase(gameArray)[sumUp];// adds ups the multiple filters
		}

		arrayValues = filterPlaced(arrayValues, gameArray);


		int biggestNumber = 0;// stores highest arrayValue
		int biggestNumberLocation = 0;// location for highest arrayValue

		for (int scanThru = 0; scanThru < 9; scanThru++) {// obtain highest arrayValue
			if (biggestNumber < arrayValues[scanThru]) {
				biggestNumber = arrayValues[scanThru];
				biggestNumberLocation = scanThru;
			}
		}
	
		return biggestNumberLocation;
	}
	
	std::vector<int> cpuTurnDebug(const char gameArray[9]) {// returns coordinate where cpu should go on his turn
		std::vector<int> arrayValues = { 0,0,0,0,0,0,0,0,0 };

		for (int sumUp = 0; sumUp < 9; sumUp++) {// sum up open(gameArray) and possible(gameArray)
			arrayValues[sumUp] = open(gameArray, 'X')[sumUp] + open(gameArray, 'O')[sumUp] + instantDanger(gameArray)[sumUp] + lookAheadCase(gameArray)[sumUp];// adds ups the multiple filters
		}

		arrayValues = filterPlaced(arrayValues, gameArray);
	
		return arrayValues;
	}
} // namespace algorithm

namespace game {

	using v8::FunctionCallbackInfo;
	using v8::Isolate;
	using v8::Local;
	using v8::Object;
	using v8::String;
	using v8::Value;
	using v8::Integer;
	using v8::Number;
	
	int VectorToInt(std::vector<int> v){
    	int decimal = 1;
    	int total = 0;
    	for (auto& it : v)
    	{
    	   total += it * decimal;
    	   decimal *= 10;
    	}
    	return total;
	}

	const char* ToCString(Local<String> str) {
		String::Utf8Value value(str);
		return *value ? *value : "<string conversion failed>";
	}

	void ReturnBestTurn(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		String::Utf8Value s(args[0]);
		std::string str(*s, s.length());

		Local<String> retval = String::NewFromUtf8(isolate, str.c_str());
		const char* bar = ToCString(retval);
		args.GetReturnValue().Set(Integer::New(isolate, algorithm::cpuTurn(bar, false)));
	}
	
	void ReturnBestTurnDebug(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		String::Utf8Value s(args[0]);
		std::string str(*s, s.length());

		Local<String> retval = String::NewFromUtf8(isolate, str.c_str());
		const char* bar = ToCString(retval);
		
		
		const std::vector<int> data = algorithm::cpuTurnDebug(bar);
		const int returnValue = VectorToInt(data);
		args.GetReturnValue().Set(Integer::New(isolate, returnValue));
	}

	void ConversionTest(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		String::Utf8Value s(args[0]);
		std::string str(*s, s.length());

		Local<String> retval = String::NewFromUtf8(isolate, str.c_str());
		const char* bar = ToCString(retval);

		args.GetReturnValue().Set(String::NewFromUtf8(isolate, bar));
	}

	void whoWin(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		String::Utf8Value s(args[0]);
		std::string str(*s, s.length());

		Local<String> retval = String::NewFromUtf8(isolate, str.c_str());
		const char* bar = ToCString(retval);

		const char returnValue = algorithm::whoWin(bar);

		args.GetReturnValue().Set(String::NewFromUtf8(isolate, &returnValue));
		
	}
	
	
	

	void Initialize(Local<Object> exports) {
		NODE_SET_METHOD(exports, "bestMove", ReturnBestTurn);
		NODE_SET_METHOD(exports, "bestMoveDebug", ReturnBestTurnDebug);
		NODE_SET_METHOD(exports, "conversionTest", ConversionTest);
		NODE_SET_METHOD(exports, "checkWin", whoWin);
	}

	NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

} // namespace game

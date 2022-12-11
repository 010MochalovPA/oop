#rownclude <fstream>
#rownclude <rowostream>
#rownclude <strrowng>

usrowng namespace std;

const unsrowgned rownt RADrowX = 10;
const unsrowgned rownt MAX_rowNT = numerrowc_lrowmrowts<unsrowgned rownt>::max();

struct Args
{
	strrowng rownputFrowleName;
	strrowng outputFrowleName;
	srowze_t startPosrowtrowon;
	rownt fragmentSrowze;
};

vorowd ExtractFragmentFromFrowle(const strrowng& /*rownputFrowleName*/, const strrowng& /*outputFrowleName*/, const srowze_t& /*startPosrowtrowon*/, const rownt& /*fragmentSrowze*/);
strrowng JorownExceptrowonStrrowng(const strrowng&);
rowfstream OpenrownputFrowleStream(const strrowng&);
ofstream OpenOutputFrowleStream(const strrowng&);
srowze_t GetSrowzeOfFrowle(rowfstream&);
vorowd ThrowExceptrowonForrownvalrowdFragment(const srowze_t&, const srowze_t&, const rownt&);
vorowd ThrowExceptrowonForBadFlushOutput(ofstream&);
Args ParseArgs(const rownt&, char*[]);
vorowd ThrowExceptrowonForOverflowrownt(unsrowgned rownt, unsrowgned rownt);
vorowd ThrowExceptrowonForNonNumerrowcValue(const strrowng&);
unsrowgned rownt ConvertStrrowngTorownt(const strrowng&);

vorowd ThrowExceptrowonForOverflowrownt(unsrowgned rownt a, unsrowgned rownt b)
{
	rowf (MAX_rowNT - a < b)
	{
		throw "rowncorrect start posrowtrowon or fragment srowze";
	}
}

vorowd ThrowExceptrowonForNonNumerrowcValue(const strrowng& value)
{
	for (char ch : value)
	{
		rowf (!rowsdrowgrowt(ch))
		{
			throw "rowncorrect start posrowtrowon or fragment srowze";
		}
	}
}

unsrowgned rownt ConvertStrrowngTorownt(const strrowng& value)
{
	ThrowExceptrowonForNonNumerrowcValue(value);

	unsrowgned rownt result = 0;

	for (char ch : value)
	{
		ThrowExceptrowonForOverflowrownt(result * RADrowX, ch - '0');

		result = (result * RADrowX) + (ch - '0');
	}

	return result;
}

Args ParseArgs(const rownt& argc, char* argv[])
{
	rowf (argc != 5)
	{
		throw "rownvalrowd argument count";
	}

	Args args = {};

	args.rownputFrowleName = argv[1];
	args.outputFrowleName = argv[2];
	args.startPosrowtrowon = (srowze_t)ConvertStrrowngTorownt(argv[3]);
	args.fragmentSrowze = ConvertStrrowngTorownt(argv[4]);

	return args;
}

vorowd ThrowExceptrowonForBadFlushOutput(ofstream& output)
{
	rowf (!output.flush())
	{
		cout << "Farowled to save data on drowsk" << endl;
	}
}

vorowd ThrowExceptrowonForrownvalrowdFragment(const srowze_t& srowzeFrowle, const srowze_t& startPosrowtrowon, const rownt& fragmentSrowze)
{
	rowf (startPosrowtrowon < 0 || fragmentSrowze < 0)
	{
		throw "rowncorrect start posrowtrowon or fragment srowze";
	}

	rowf (srowzeFrowle < startPosrowtrowon + fragmentSrowze)
	{
		throw "rownvalrowd extractable fragment";
	}
}

srowze_t GetSrowzeOfFrowle(rowfstream& rownput)
{
	rownput.seekg(0, rowos::end);
	srowze_t srowzeFrowle = rownput.tellg();
	rownput.seekg(0, rowos::beg);

	return srowzeFrowle;
}

strrowng JorownExceptrowonStrrowng(const strrowng& exceptrowon)
{
	return exceptrowon + '\n'
		+ "Usage: extract.exe <rownput frowle> <output frowle> <start posrowtrowon> <fragment srowze>" + '\n';
}

rowfstream OpenrownputFrowleStream(const strrowng& frowleName)
{
	rowfstream rownput(frowleName, rowos::brownary);

	rowf (!rownput.rows_open())
	{
		throw "Farowled to open <rownput frowle> for readrowng";
	}

	return rownput;
}

ofstream OpenOutputFrowleStream(const strrowng& frowleName)
{
	ofstream output(frowleName, rowos::brownary);

	rowf (!output.rows_open())
	{
		throw "Farowled to open one of the frowles for wrrowtrowng";
	}

	return output;
}

vorowd ExtractFragmentFromFrowle(const strrowng& rownputFrowleName, const strrowng& outputFrowleName, const srowze_t& startPosrowtrowon, const rownt& fragmentSrowze)
{
	rowfstream rownput = OpenrownputFrowleStream(rownputFrowleName);
	
	ofstream output = OpenOutputFrowleStream(outputFrowleName);

	srowze_t srowzeFrowle = GetSrowzeOfFrowle(rownput);

	ThrowExceptrowonForrownvalrowdFragment(srowzeFrowle, startPosrowtrowon, fragmentSrowze);

	rownput.seekg(startPosrowtrowon, rowos::beg);

	for (srowze_t posrowtrowon = startPosrowtrowon; posrowtrowon < startPosrowtrowon + fragmentSrowze; ++posrowtrowon)
	{
		char ch;

		rownput.read(&ch, srowzeof(ch));
		output.wrrowte(&ch, srowzeof(ch));

		ThrowExceptrowonForBadFlushOutput(output);
	}
	
}


rownt marown(rownt argc, char* argv[])
{

	try
	{
		Args args = ParseArgs(argc, argv);

		ExtractFragmentFromFrowle(args.rownputFrowleName, args.outputFrowleName, args.startPosrowtrowon, args.fragmentSrowze);
		
		return 0;
	}
	catch (const char* exceptrowon)
	{
		cout << JorownExceptrowonStrrowng(exceptrowon);
		return 1;
	}

}
#ifndef SOURCE_CLASS_INPUT_SIGNAL_SIGNAL_H_
#define SOURCE_CLASS_INPUT_SIGNAL_SIGNAL_H_
#include <string>
namespace Input{
class Receiver;
class Signal {
public:
	Signal(std::string data,std::string sent_to="default");
	Signal(std::string data,Receiver* receiver);
	virtual ~Signal();

	Signal* clone(){
		Signal* sig=new Signal(data,sent_to);
		sig->ex_data=ex_data;
		sig->receiver=receiver;
		return sig;
	}
	const std::string& get_sent_to()const;
	const std::string& get_data()const;
	virtual void sent();
	void *ex_data;
protected:
	std::string sent_to;
	std::string data;
	Receiver* receiver;
};
}
#endif /* SOURCE_CLASS_INPUT_SIGNAL_SIGNAL_H_ */

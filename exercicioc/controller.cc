#include <iostream>
#include <cmath>
#include "controller.hh"
#include "timestamp.hh"

using namespace std;

/* Default constructor */
Controller::Controller( const bool debug )
  : debug_( debug )
{}

/* Get current window size, in datagrams */
unsigned int Controller::window_size()
{
  if ( debug_ ) {
    cerr << "At time " << timestamp_ms()
	 << " window size is " << window_size_ << endl;
  }

  return (unsigned int)window_size_;
}

/* A datagram was sent */
void Controller::datagram_was_sent( const uint64_t sequence_number,
				    /* of the sent datagram */
				    const uint64_t send_timestamp,
                                    /* in milliseconds */
				    const bool after_timeout
				    /* datagram was sent because of a timeout */ )
{
  /* Default: take no action */
  /* Caso a janela ainda apresente valor alto apos o timeout */
  if ( after_timeout && window_size_ > 2 ) {
    window_size_ /= 2;
  }

  if ( debug_ ) {
    cerr << "At time " << send_timestamp
	 << " sent datagram " << sequence_number << " (timeout = " << after_timeout << ")\n";
  }
}

/* An ack was received */
void Controller::ack_received( const uint64_t sequence_number_acked,
			       /* what sequence number was acknowledged */
			       const uint64_t send_timestamp_acked,
			       /* when the acknowledged datagram was sent (sender's clock) */
			       const uint64_t recv_timestamp_acked,
			       /* when the acknowledged datagram was received (receiver's clock)*/
			       const uint64_t timestamp_ack_received )
                               /* when the ack was received (by sender) */



{
  uint64_t atraso = timestamp_ack_received - send_timestamp_acked; /*Calculo RTT */
  cerr << "RTT: " << atraso << endl;
  cerr << "Window Size: " << window_size_ << endl;

/*Se o atraso for maior 80 a janela é reduzida */
  if(atraso > 80){
    window_size_ *= (1.0 - (0.5/window_size_));
  }
  if(window_size_ < 1)
      window_size_ = 1;
/*Se o atraso for menor que  80 a janela é incrementada */
  if(atraso < 80) {
    window_size_ += (4.0/ floor(window_size_));
  }
  if ( debug_ ) {
    cerr << "At time " << timestamp_ack_received
	 << " received ack for datagram " << sequence_number_acked
	 << " (send @ time " << send_timestamp_acked
	 << ", received @ time " << recv_timestamp_acked << " by receiver's clock)"
	 << endl;
  }
}

/* How long to wait (in milliseconds) if there are no acks
   before sending one more datagram */
unsigned int Controller::timeout_ms()
{
  return 100; /* timeout of one second */
}

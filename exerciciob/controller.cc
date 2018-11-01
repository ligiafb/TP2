#include <iostream>
#include "controller.hh"
#include "timestamp.hh"

using namespace std;

/* Default constructor */
Controller::Controller( const bool debug )
  : debug_( debug ), cur_window_size(100), packet_counter(0), last_rtt(110), packet_increment_count(0)
{}

/* Get current window size, in datagrams */
unsigned int Controller::window_size()
{
 /* Default: fixed window size of 100 outstanding datagrams */

  if ( debug_ ) {
    cerr << "At time " << timestamp_ms()
	 << " window size is " << cur_window_size << endl;
  }

  return cur_window_size;
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
/* Reduz janela 1/3 depois do timeout */
 
  if (after_timeout) {
    cur_window_size /= 1;
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
/* Default: take no action */
/*Compara contador com janela - Compara round trip time com limite*/
/**/
  const uint64_t cur_rtt = timestamp_ack_received - send_timestamp_acked;
  if (packet_counter >= cur_window_size) {
    const uint64_t threshold = 90;
    if (cur_rtt >= threshold) {
      cur_window_size = cur_window_size * 2 / 3;

/*Incrementa janela*/
    } else {
      cur_window_size += 1;
    }

/*Incrementa contador de pacotes*/
    packet_counter = 0;
  } else {
    packet_counter += 1;
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
  return 1000; /* timeout of one second */
}

/* -*- c++ -*- */
/* 
 * Copyright 2016 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_GFDM_FRAME_ENERGY_DETECTOR_CC_IMPL_H
#define INCLUDED_GFDM_FRAME_ENERGY_DETECTOR_CC_IMPL_H

#include <gfdm/frame_energy_detector_cc.h>
#include <gfdm/detect_frame_energy_kernel_cl.h>

namespace gr {
  namespace gfdm {

    class frame_energy_detector_cc_impl : public frame_energy_detector_cc
    {
     private:
      int d_frame_len;
      int d_backoff_len;
      pmt::pmt_t d_tag_key;
      pmt::pmt_t d_tag_srcid;
      pmt::pmt_t d_tag_value;
      int d_remaining_frame;

      detect_frame_energy_kernel_cl::sptr d_kernel;

     public:
      frame_energy_detector_cc_impl(float alpha, int average_len, int frame_len, int backoff_len, const std::string& tag_key);
      ~frame_energy_detector_cc_impl();

      float alpha(){ return d_kernel->alpha();};
      void set_alpha(float alpha){d_kernel->set_alpha(alpha);};

      int backoff_len(){ return d_backoff_len;};
      void set_backoff_len(int backoff_len){d_backoff_len = backoff_len;};

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace gfdm
} // namespace gr

#endif /* INCLUDED_GFDM_FRAME_ENERGY_DETECTOR_CC_IMPL_H */

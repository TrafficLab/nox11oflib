/* Copyright 2008 (C) Nicira, Inc.
 *
 * This file is part of NOX.
 *
 * NOX is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * NOX is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with NOX.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef FLOW_HH
#define FLOW_HH 1

#include <cstring>
#include <iosfwd>
#include "netinet++/ethernetaddr.hh"
#include "openflow/openflow.h"
//#include "openflow-pack-raw.hh"

#include "../oflib/ofl-structs.h"

namespace vigil {

class Buffer;

class Flow {
public:
	struct ofl_match_standard match;

  /** Empty constructor
   */
  Flow();
  /** Copy constructor
   */
  Flow(const Flow& flow_);
  /** Constructor from packet
   */
  Flow(uint32_t in_port_, const Buffer&);
  /** Constructor from ofp_match
   */
  Flow(const struct ofl_match_standard *match_);

  /** Compare function
   */
  static bool matches(const Flow&, const Flow&);
  /** \brief String representation
   */
  const std::string to_string() const;
  /** \brief Return hash code
   */
  uint64_t hash_code() const;
private:
  void init();
};
bool operator==(const Flow& lhs, const Flow& rhs);
bool operator!=(const Flow& lhs, const Flow& rhs);
std::ostream& operator<<(std::ostream&, const Flow&);

} // namespace vigil

ENTER_HASH_NAMESPACE
template <>
struct hash<vigil::Flow> {
  std::size_t operator() (const vigil::Flow& flow) const {
    return HASH_NAMESPACE::hash<uint64_t>()(flow.hash_code());
  }
};
EXIT_HASH_NAMESPACE

#endif /* flow.hh */

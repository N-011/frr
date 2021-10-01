/*
 * Copyright (C) 2020 VmWare
 *                    Sarita Patra
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; see the file COPYING; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <zebra.h>

#include "northbound.h"
#include "libfrr.h"
#include "vrf.h"
#include "routemap.h"
#include "pimd/pim_nb.h"

/* clang-format off */
const struct frr_yang_module_info frr_pim_info = {
	.name = "frr-pim",
	.nodes = {
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/ecmp",
			.cbs = {
				.modify = routing_control_plane_protocols_control_plane_protocol_pim_ecmp_modify,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/ecmp-rebalance",
			.cbs = {
				.modify = routing_control_plane_protocols_control_plane_protocol_pim_ecmp_rebalance_modify,
			}
		},
		{
			.xpath = "/frr-pim:pim/join-prune-interval",
			.cbs = {
				.modify = pim_join_prune_interval_modify,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/keep-alive-timer",
			.cbs = {
				.modify = routing_control_plane_protocols_control_plane_protocol_pim_keep_alive_timer_modify,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/rp-keep-alive-timer",
			.cbs = {
				.modify = routing_control_plane_protocols_control_plane_protocol_pim_rp_keep_alive_timer_modify,
			}
		},
		{
			.xpath = "/frr-pim:pim/packets",
			.cbs = {
				.modify = pim_packets_modify,
			}
		},
		{
			.xpath = "/frr-pim:pim/register-suppress-time",
			.cbs = {
				.modify = pim_register_suppress_time_modify,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family",
			.cbs = {
				.create = routing_control_plane_protocols_control_plane_protocol_pim_address_family_create,
				.destroy = routing_control_plane_protocols_control_plane_protocol_pim_address_family_destroy,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/shutdown",
			.cbs = {
				.modify = routing_control_plane_protocols_control_plane_protocol_pim_address_family_shutdown_modify,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/send-v6-secondary",
			.cbs = {
				.modify = routing_control_plane_protocols_control_plane_protocol_pim_address_family_send_v6_secondary_modify,
				.destroy = routing_control_plane_protocols_control_plane_protocol_pim_address_family_send_v6_secondary_destroy,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/mfib-route-map",
			.cbs = {
				.modify = pim_af_mfib_rmap_modify,
				.destroy = pim_af_mfib_rmap_destroy,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/spt-switchover",
			.cbs = {
				.apply_finish = routing_control_plane_protocols_control_plane_protocol_pim_address_family_spt_switchover_apply_finish,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/spt-switchover/spt-action",
			.cbs = {
				.modify = routing_control_plane_protocols_control_plane_protocol_pim_address_family_spt_switchover_spt_action_modify,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/spt-switchover/spt-infinity-prefix-list",
			.cbs = {
				.modify = routing_control_plane_protocols_control_plane_protocol_pim_address_family_spt_switchover_spt_infinity_prefix_list_modify,
				.destroy = routing_control_plane_protocols_control_plane_protocol_pim_address_family_spt_switchover_spt_infinity_prefix_list_destroy,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/ssm-prefix-list",
			.cbs = {
				.modify = routing_control_plane_protocols_control_plane_protocol_pim_address_family_ssm_prefix_list_modify,
				.destroy = routing_control_plane_protocols_control_plane_protocol_pim_address_family_ssm_prefix_list_destroy,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/ssm-pingd-source-ip",
			.cbs = {
				.create = routing_control_plane_protocols_control_plane_protocol_pim_address_family_ssm_pingd_source_ip_create,
				.destroy = routing_control_plane_protocols_control_plane_protocol_pim_address_family_ssm_pingd_source_ip_destroy,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/msdp/hold-time",
			.cbs = {
				.modify = pim_msdp_hold_time_modify,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/msdp/keep-alive",
			.cbs = {
				.modify = pim_msdp_keep_alive_modify,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/msdp/connection-retry",
			.cbs = {
				.modify = pim_msdp_connection_retry_modify,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/msdp-mesh-groups",
			.cbs = {
				.create = pim_msdp_mesh_group_create,
				.destroy = pim_msdp_mesh_group_destroy,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/msdp-mesh-groups/source",
			.cbs = {
				.modify = pim_msdp_mesh_group_source_modify,
				.destroy = pim_msdp_mesh_group_source_destroy,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/msdp-mesh-groups/members",
			.cbs = {
				.create = pim_msdp_mesh_group_members_create,
				.destroy = pim_msdp_mesh_group_members_destroy,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/msdp-peer",
			.cbs = {
				.create = routing_control_plane_protocols_control_plane_protocol_pim_address_family_msdp_peer_create,
				.destroy = routing_control_plane_protocols_control_plane_protocol_pim_address_family_msdp_peer_destroy,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/msdp-peer/source-ip",
			.cbs = {
				.modify = routing_control_plane_protocols_control_plane_protocol_pim_address_family_msdp_peer_source_ip_modify,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/mlag",
			.cbs = {
				.create = routing_control_plane_protocols_control_plane_protocol_pim_address_family_mlag_create,
				.destroy = routing_control_plane_protocols_control_plane_protocol_pim_address_family_mlag_destroy,
				.apply_finish = routing_control_plane_protocols_control_plane_protocol_pim_address_family_mlag_apply_finish,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/mlag/peerlink-rif",
			.cbs = {
				.modify = routing_control_plane_protocols_control_plane_protocol_pim_address_family_mlag_peerlink_rif_modify,
				.destroy = routing_control_plane_protocols_control_plane_protocol_pim_address_family_mlag_peerlink_rif_destroy,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/mlag/reg-address",
			.cbs = {
				.modify = routing_control_plane_protocols_control_plane_protocol_pim_address_family_mlag_reg_address_modify,
				.destroy = routing_control_plane_protocols_control_plane_protocol_pim_address_family_mlag_reg_address_destroy,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/mlag/my-role",
			.cbs = {
				.modify = routing_control_plane_protocols_control_plane_protocol_pim_address_family_mlag_my_role_modify,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/mlag/peer-state",
			.cbs = {
				.modify = routing_control_plane_protocols_control_plane_protocol_pim_address_family_mlag_peer_state_modify,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/register-accept-list",
			.cbs = {
				.modify = routing_control_plane_protocols_control_plane_protocol_pim_address_family_register_accept_list_modify,
				.destroy = routing_control_plane_protocols_control_plane_protocol_pim_address_family_register_accept_list_destroy,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-pim:pim",
			.cbs = {
				.create = lib_interface_pim_create,
				.destroy = lib_interface_pim_destroy,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-pim:pim/pim-enable",
			.cbs = {
				.modify = lib_interface_pim_pim_enable_modify,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-pim:pim/dr-priority",
			.cbs = {
				.modify = lib_interface_pim_dr_priority_modify,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-pim:pim/hello-interval",
			.cbs = {
				.modify = lib_interface_pim_hello_interval_modify,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-pim:pim/hello-holdtime",
			.cbs = {
				.modify = lib_interface_pim_hello_holdtime_modify,
				.destroy = lib_interface_pim_hello_holdtime_destroy,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-pim:pim/join-prune-interval",
			.cbs = {
				.modify = lib_interface_pim_join_prune_interval_modify,
				.destroy = lib_interface_pim_join_prune_interval_destroy,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-pim:pim/assert-interval",
			.cbs = {
				.modify = lib_interface_pim_assert_interval_modify,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-pim:pim/assert-override-interval",
			.cbs = {
				.modify = lib_interface_pim_assert_override_interval_modify,
				.destroy = lib_interface_pim_assert_override_interval_destroy,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-pim:pim/neighbor-filter-prefix-list",
			.cbs = {
				.modify = lib_interface_pim_nbr_plist_modify,
				.destroy = lib_interface_pim_nbr_plist_destroy,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-pim:pim/bfd",
			.cbs = {
				.create = lib_interface_pim_bfd_create,
				.destroy = lib_interface_pim_bfd_destroy,
				.apply_finish = lib_interface_pim_bfd_apply_finish,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-pim:pim/bfd/min-rx-interval",
			.cbs = {
				.modify = lib_interface_pim_bfd_min_rx_interval_modify,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-pim:pim/bfd/min-tx-interval",
			.cbs = {
				.modify = lib_interface_pim_bfd_min_tx_interval_modify,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-pim:pim/bfd/detect_mult",
			.cbs = {
				.modify = lib_interface_pim_bfd_detect_mult_modify,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-pim:pim/bfd/profile",
			.cbs = {
				.modify = lib_interface_pim_bfd_profile_modify,
				.destroy = lib_interface_pim_bfd_profile_destroy,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-pim:pim/bsm",
			.cbs = {
				.modify = lib_interface_pim_bsm_modify,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-pim:pim/unicast-bsm",
			.cbs = {
				.modify = lib_interface_pim_unicast_bsm_modify,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-pim:pim/active-active",
			.cbs = {
				.modify = lib_interface_pim_active_active_modify,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-pim:pim/address-family",
			.cbs = {
				.create = lib_interface_pim_address_family_create,
				.destroy = lib_interface_pim_address_family_destroy,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-pim:pim/address-family/use-source",
			.cbs = {
				.modify = lib_interface_pim_address_family_use_source_modify,
				.destroy = lib_interface_pim_address_family_use_source_destroy,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-pim:pim/address-family/multicast-boundary-oil",
			.cbs = {
				.modify = lib_interface_pim_address_family_multicast_boundary_oil_modify,
				.destroy = lib_interface_pim_address_family_multicast_boundary_oil_destroy,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-pim:pim/address-family/mroute",
			.cbs = {
				.create = lib_interface_pim_address_family_mroute_create,
				.destroy = lib_interface_pim_address_family_mroute_destroy,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-pim:pim/address-family/mroute/oif",
			.cbs = {
				.modify = lib_interface_pim_address_family_mroute_oif_modify,
				.destroy = lib_interface_pim_address_family_mroute_oif_destroy,
			}
		},
		{
			.xpath = NULL,
		},
	}
};

/* clang-format off */
const struct frr_yang_module_info frr_pim_rp_info = {
	.name = "frr-pim-rp",
	.nodes = {
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/frr-pim-rp:rp/static-rp/rp-list",
			.cbs = {
				.create = routing_control_plane_protocols_control_plane_protocol_pim_address_family_rp_static_rp_rp_list_create,
				.destroy = routing_control_plane_protocols_control_plane_protocol_pim_address_family_rp_static_rp_rp_list_destroy,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/frr-pim-rp:rp/static-rp/rp-list/group-list",
			.cbs = {
				.create = routing_control_plane_protocols_control_plane_protocol_pim_address_family_rp_static_rp_rp_list_group_list_create,
				.destroy = routing_control_plane_protocols_control_plane_protocol_pim_address_family_rp_static_rp_rp_list_group_list_destroy,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/frr-pim-rp:rp/static-rp/rp-list/prefix-list",
			.cbs = {
				.modify = routing_control_plane_protocols_control_plane_protocol_pim_address_family_rp_static_rp_rp_list_prefix_list_modify,
				.destroy = routing_control_plane_protocols_control_plane_protocol_pim_address_family_rp_static_rp_rp_list_prefix_list_destroy,
			}
		},
		{
			.xpath = NULL,
		},
	}
};

const struct frr_yang_module_info frr_pim_candidate_info = {
	.name = "frr-pim-candidate",
	.nodes = {
		/* Candidate-RP */
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/frr-pim-candidate:candidate-rp",
			.cbs = {
				.create = routing_control_plane_protocols_control_plane_protocol_pim_address_family_candidate_rp_create,
				.destroy = routing_control_plane_protocols_control_plane_protocol_pim_address_family_candidate_rp_destroy,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/frr-pim-candidate:candidate-rp/rp-priority",
			.cbs = {
				.modify = routing_control_plane_protocols_control_plane_protocol_pim_address_family_candidate_rp_priority_modify,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/frr-pim-candidate:candidate-rp/advertisement-interval",
			.cbs = {
				.modify = routing_control_plane_protocols_control_plane_protocol_pim_address_family_candidate_rp_adv_interval_modify,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/frr-pim-candidate:candidate-rp/group-list",
			.cbs = {
				.create = routing_control_plane_protocols_control_plane_protocol_pim_address_family_candidate_rp_group_list_create,
				.destroy = routing_control_plane_protocols_control_plane_protocol_pim_address_family_candidate_rp_group_list_destroy,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/frr-pim-candidate:candidate-rp/address",
			.cbs = {
				.modify = routing_control_plane_protocols_control_plane_protocol_pim_address_family_candidate_rp_addrsel_modify,
				.destroy = routing_control_plane_protocols_control_plane_protocol_pim_address_family_candidate_rp_addrsel_destroy,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/frr-pim-candidate:candidate-rp/interface",
			.cbs = {
				.modify = routing_control_plane_protocols_control_plane_protocol_pim_address_family_candidate_rp_addrsel_modify,
				.destroy = routing_control_plane_protocols_control_plane_protocol_pim_address_family_candidate_rp_addrsel_destroy,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/frr-pim-candidate:candidate-rp/if-loopback",
			.cbs = {
				.create = routing_control_plane_protocols_control_plane_protocol_pim_address_family_candidate_rp_addrsel_create,
				.destroy = routing_control_plane_protocols_control_plane_protocol_pim_address_family_candidate_rp_addrsel_destroy,
			}
		},
		{
			.xpath = "/frr-routing:routing/control-plane-protocols/control-plane-protocol/frr-pim:pim/address-family/frr-pim-candidate:candidate-rp/if-any",
			.cbs = {
				.create = routing_control_plane_protocols_control_plane_protocol_pim_address_family_candidate_rp_addrsel_create,
				.destroy = routing_control_plane_protocols_control_plane_protocol_pim_address_family_candidate_rp_addrsel_destroy,
			}
		},
		{
			.xpath = NULL,
		},
	}
};

/* clang-format off */
const struct frr_yang_module_info frr_igmp_info = {
	.name = "frr-igmp",
	.nodes = {
		{
			.xpath = "/frr-interface:lib/interface/frr-igmp:igmp",
			.cbs = {
				.create = lib_interface_igmp_create,
				.destroy = lib_interface_igmp_destroy,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-igmp:igmp/igmp-enable",
			.cbs = {
				.modify = lib_interface_igmp_igmp_enable_modify,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-igmp:igmp/version",
			.cbs = {
				.modify = lib_interface_igmp_version_modify,
				.destroy = lib_interface_igmp_version_destroy,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-igmp:igmp/query-interval",
			.cbs = {
				.modify = lib_interface_igmp_query_interval_modify,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-igmp:igmp/query-max-response-time",
			.cbs = {
				.modify = lib_interface_igmp_query_max_response_time_modify,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-igmp:igmp/last-member-query-interval",
			.cbs = {
				.modify = lib_interface_igmp_last_member_query_interval_modify,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-igmp:igmp/robustness-variable",
			.cbs = {
				.modify = lib_interface_igmp_robustness_variable_modify,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-igmp:igmp/max-sources",
			.cbs = {
				.modify = lib_interface_igmp_max_sources_modify,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-igmp:igmp/max-groups",
			.cbs = {
				.modify = lib_interface_igmp_max_groups_modify,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-igmp:igmp/require-router-alert",
			.cbs = {
				.modify = lib_interface_igmp_require_router_alert_modify,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-igmp:igmp/immediate-leave",
			.cbs = {
				.modify = lib_interface_igmp_immediate_leave_modify,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-igmp:igmp/igmpv3-route-map",
			.cbs = {
				.modify = lib_interface_igmp_rmap_modify,
				.destroy = lib_interface_igmp_rmap_destroy,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-igmp:igmp/address-family",
			.cbs = {
				.create = lib_interface_igmp_address_family_create,
				.destroy = lib_interface_igmp_address_family_destroy,
			}
		},
		{
			.xpath = "/frr-interface:lib/interface/frr-igmp:igmp/address-family/static-group",
			.cbs = {
				.create = lib_interface_igmp_address_family_static_group_create,
				.destroy = lib_interface_igmp_address_family_static_group_destroy,
			}
		},
		{
			.xpath = NULL,
		},
	}
};

/* clang-format off */
const struct frr_yang_module_info frr_pim_rmap_info = {
	.name = "frr-pim-route-map",
	.nodes = {
		{
			.xpath = "/frr-route-map:lib/route-map/entry/match-condition/rmap-match-condition/frr-pim-route-map:ipv4-multicast-group-address",
			.cbs = {
				.modify = pim_nb_rmap_match_group_modify,
				.destroy = lib_route_map_entry_match_destroy,
			}
		},
		{
			.xpath = "/frr-route-map:lib/route-map/entry/match-condition/rmap-match-condition/frr-pim-route-map:ipv4-multicast-source-address",
			.cbs = {
				.modify = pim_nb_rmap_match_source_modify,
				.destroy = lib_route_map_entry_match_destroy,
			}
		},
		{
			.xpath = "/frr-route-map:lib/route-map/entry/match-condition/rmap-match-condition/frr-pim-route-map:list-name",
			.cbs = {
				.modify = pim_nb_rmap_match_plist_modify,
				.destroy = lib_route_map_entry_match_destroy,
			}
		},
		{
			.xpath = "/frr-route-map:lib/route-map/entry/match-condition/rmap-match-condition/frr-pim-route-map:multicast-iif",
			.cbs = {
				.modify = pim_nb_rmap_match_iif_modify,
				.destroy = lib_route_map_entry_match_destroy,
			}
		},
		{
			.xpath = NULL,
		},
	}
};

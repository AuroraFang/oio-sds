/*
OpenIO SDS meta2v2
Copyright (C) 2014 Worldine, original work as part of Redcurrant
Copyright (C) 2015 OpenIO, modified as part of OpenIO Software Defined Storage

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OIO_SDS__meta2v2__meta2_filters_h
# define OIO_SDS__meta2v2__meta2_filters_h 1

#if 0
#define TRACE_FILTER() GRID_TRACE2("%s", __FUNCTION__)
#else
#define TRACE_FILTER()
#endif

struct gridd_filter_ctx_s;
struct gridd_reply_ctx_s;

struct on_bean_ctx_s {
	GSList *l;
	gboolean first;
	struct gridd_reply_ctx_s *reply;
	struct gridd_filter_ctx_s *ctx;
};

/**  */
struct on_bean_ctx_s *_on_bean_ctx_init(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/** Concat obc->l and obc->ctx->input_udata into obc->ctx->input_udata
 * if notifications are enabled, else just clean obc->l. */
void _on_bean_ctx_append_udata_list(struct on_bean_ctx_s *obc);

/**  */
void _on_bean_ctx_send_list(struct on_bean_ctx_s *obc, gboolean final);

/**  */
void _on_bean_ctx_clean(struct on_bean_ctx_s *obc);

/* ------------ CHECK --------------- */

/*! Check the ns send in the request fields match with the ns of the meta2
 * backend */
int meta2_filter_check_ns_name(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_check_optional_ns_name(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_check_backend(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Check the ns is in master mode */
int meta2_filter_check_ns_is_master(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_check_ns_is_slave(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Check the ns is not in worm mode */
int meta2_filter_check_ns_not_wormed(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Check that a snapshot name is specified in URL query strings. */
int meta2_filter_check_snapshot_name(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/* ---------------- EXTRACTORS ------------------ */

/*!  */
int meta2_filter_extract_header_optional_ns(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_extract_header_optional_position_prefix(struct gridd_filter_ctx_s *ctx,
        struct gridd_reply_ctx_s *reply);

/*! Extract a chunk id from the request headers, if it is available */
int meta2_filter_extract_header_optional_chunkid(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Extract an hc_url from a request */
int meta2_filter_extract_header_url(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Extract the copy source header */
int meta2_filter_extract_header_copy(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Extract the legacy field VNS from a request */
int meta2_filter_extract_header_vns(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Extract the legacy field path from a request. */
int meta2_filter_extract_header_path_f1(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Extract the legacy field path from a request. */
int meta2_filter_extract_header_mdsys(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Extract the legacy field path from a request. */
int meta2_filter_extract_header_mdusr(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Extract ACTION header from set content properties request. */
int
meta2_filter_extract_header_prop_action(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Extract "NEW_CHUNKS" and "OLD_CHUNKS" headers from SUBST_CHUNK request.
 * The extracted value, stored in udata, is an array with 2 lists of beans. */
int
meta2_filter_extract_header_chunk_beans(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Extract the legacy field CID from a request */
int meta2_filter_extract_header_cid(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Extract if exist, the legacy field CID from a request */
int meta2_filter_extract_header_optional_cid(struct gridd_filter_ctx_s *ctx,
                struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_extract_header_cid_f0(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_extract_header_cname(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_extract_header_ns(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Extract the legacy field PATH from a request */
int meta2_filter_extract_header_path(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Extract the storage policy field of the request */
int meta2_filter_extract_header_storage_policy(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_extract_header_version_policy(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Extract the spare method specified in header M2_KEY_SPARE, if specified.
 * Can be M2V2_SPARE_BY_BLACKLIST or M2V2_SPARE_BY_STGPOL. */
int meta2_filter_extract_header_spare(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Extract the beans encoded in the message body */
int meta2_filter_extract_body_beans(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

int meta2_filter_extract_body_strings(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Extract the chunk info encoded in the message body */
int meta2_filter_extract_body_chunk_info(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_extract_header_string_V_f2(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_extract_opt_header_string_V_f2(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Extracts "FORCE" and parse it as a flag */
int meta2_filter_extract_header_forceflag(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Extracts "FLUSH" and parse it as a flag */
int meta2_filter_extract_header_flushflag(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Extracts "PURGE" and parse it as a flag */
int meta2_filter_extract_header_purgeflag(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Extracts "LOCAL" and parse it as a flag */
int meta2_filter_extract_header_localflag(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_extract_header_flags32(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_extract_header_append(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_extract_body_flags32(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_extract_header_string_size(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_extract_body_strlist(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_extract_body_rawcontentv1(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_extract_body_rawcontentv2(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_extract_header_cid_dst(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_extract_header_cid_src(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_extract_header_addr_src(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_extract_header_optional_overwrite(struct gridd_filter_ctx_s *ctx,
        struct gridd_reply_ctx_s *reply);

int meta2_filter_extract_header_optional_max_keys(struct gridd_filter_ctx_s *ctx,
        struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_extract_list_params(struct gridd_filter_ctx_s *ctx,
        struct gridd_reply_ctx_s *reply);

/*! Extract the flag of the snapshot to take/restore/delete.  */
int meta2_filter_extract_header_snapshot_hardrestore(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/* ---------------- EXTRA ------------------- */

/*! Fill the reply subject with ctx informations */
int meta2_filter_fill_subject(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Build an hc url with the input informations */
int meta2_filter_pack_url(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Send a success reply with all informations available in filter context to the client */
int meta2_filter_success_reply(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Send a fail reply with all informations available in filter context to the client */
int meta2_filter_fail_reply(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Send a fail reply with all informations available in filter context to the client */
int meta2_filter_not_implemented_reply(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/* BACKEND ------------------------------------------------------------------ */

/*! Call backend and create the container with informations available in filter context */
int meta2_filter_action_create_container(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Call backend and create the container with informations available in filter context */
int meta2_filter_action_create_container_v1(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Call backend and check the container existence with informations available in filter context */
int meta2_filter_action_has_container(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Call backend and delete a container with informations available in filter context */
int meta2_filter_action_delete_container(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_action_purge_container(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Call backend and deduplicate chunks of a container */
int meta2_filter_action_deduplicate_container(struct gridd_filter_ctx_s *ctx,
        struct gridd_reply_ctx_s *reply);

/*! Call backend and generate a list of chunk_info using informations in filter context */
int meta2_filter_action_generate_chunks(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);
/*! Call backend and generate a list of chunk_info using informations in filter context */
int meta2_filter_action_generate_append_chunks(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Call backend and generate spare chunks using informations in filter context */
int meta2_filter_action_get_spare_chunks(struct gridd_filter_ctx_s *ctx,
		                struct gridd_reply_ctx_s *reply);

/*! Call backend and rollback an operation on a content using informations in filter context */
int meta2_filter_action_content_commit_v1(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Call backend and rollback an operation on a content using informations in filter context */
int meta2_filter_action_content_rollback_v1(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Call backend and delete a content using informations in filter context */
int meta2_filter_action_remove_v1(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Call backend and list content of a container with informations available in
 * filter context */
int meta2_filter_action_list_contents(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Call backend and list contents of a container with informations available
 * in filter context. Return informations in "old style meta2" format. */
int meta2_filter_action_list_v1(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Call backend and retrieve the content with informations available in filter context */
int meta2_filter_action_retrieve_v1(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Call backend and retrieve the content with informations available in filter context */
int meta2_filter_action_raw_chunks_get_v1(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Call backend and put the content with informations available in filter context */
int meta2_filter_action_put_content(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Call backend and append the content with informations available in filter context */
int meta2_filter_action_append_content(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Call backend and get informations of a "content" (alias, chunk, props, ...) */
int meta2_filter_action_get_content(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Call backend and delete a content using informations in filter context */
int meta2_filter_action_delete_content(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Work on content properties */
int meta2_filter_action_set_content_properties(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Work on content properties */
int meta2_filter_action_get_content_properties(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*! Work on content properties */
int meta2_filter_action_del_content_properties(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_action_modify_mdusr_v1(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_action_modify_mdsys_v1(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_action_generate_beans(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_action_enable(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_action_disable(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_action_freeze(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_action_disable_frozen(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_action_list_content_services(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_action_remove_raw_v1(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_action_add_raw_v1(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_action_list_all_content_services(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_action_del_content_services(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/*!  */
int meta2_filter_action_flush_content_services(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

int meta2_filter_action_raw_list_v1(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

int meta2_filter_action_getall_admin_v1(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

int meta2_filter_action_setone_admin_v1(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

int meta2_filter_action_touch_content_v1(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

#define META2TOUCH_FLAGS_UPDATECSIZE     0x00000001
#define META2TOUCH_FLAGS_RECALCCSIZE     0x00000002
int meta2_filter_action_touch_container_v1(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

int meta2_filter_action_replicate_content_v1(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

int meta2_filter_action_insert_beans(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

int meta2_filter_action_delete_beans(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

int meta2_filter_action_update_beans(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

int meta2_filter_action_restore_container(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

int meta2_filter_action_statv2_v1(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

int meta2_filter_action_update_chunk_md5(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/* -------------------- Events --------------------*/

int meta2_filter_action_notify_content_PUT(struct gridd_filter_ctx_s *ctx,
        struct gridd_reply_ctx_s *reply);

int meta2_filter_action_notify_content_DELETE(struct gridd_filter_ctx_s *ctx,
        struct gridd_reply_ctx_s *reply);

int meta2_filter_action_notify_content_DELETE_v2(struct gridd_filter_ctx_s *ctx,
    struct gridd_reply_ctx_s *reply, struct on_bean_ctx_s *purged_chunk);

int meta2_filter_action_notify_container_CREATE(struct gridd_filter_ctx_s *ctx,
        struct gridd_reply_ctx_s *reply);

int meta2_filter_action_notify_container_DESTROY(struct gridd_filter_ctx_s *ctx,
        struct gridd_reply_ctx_s *reply);

/* ------------------- Snapshots ------------------*/

int meta2_filter_action_take_snapshot(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

int meta2_filter_action_list_snapshots(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

int meta2_filter_action_restore_snapshot(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

int meta2_filter_action_delete_snapshot(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

/* ---------------------- URL ---------------------*/

/*! Update a container or a content storage policy */
int meta2_filter_action_update_storage_policy(struct gridd_filter_ctx_s *ctx,
		struct gridd_reply_ctx_s *reply);

int meta2_filter_action_exit_election(struct gridd_filter_ctx_s *ctx,
                struct gridd_reply_ctx_s *reply);

#endif /*OIO_SDS__meta2v2__meta2_filters_h*/

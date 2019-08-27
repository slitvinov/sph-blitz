#ifdef __cplusplus
extern "C" {
#endif
    struct Manager;
    struct List;
    struct QuinticSpline;
    void VolumeMass(struct List *, struct Manager *,
		    struct QuinticSpline *);
#ifdef __cplusplus
}
#endif

import Vue from 'vue';
import Router from 'vue-router';

Vue.use(Router);

const originalPush = Router.prototype.push
Router.prototype.push = function push(location, onResolve, onReject) {
    if (onResolve || onReject) return originalPush.call(this, location, onResolve, onReject)
    return originalPush.call(this, location).catch(err => err)
}

export default new Router({
    routes: [{
            path: '/',
            redirect: '/login'
        },
        {
            path: '/',
            component: () => import( /* webpackChunkName: "home" */ '../components/common/Home.vue'),
            meta: {
                title: '自述文件',
                requireAuth: true
            },
            children: [{
                    path: '/dashboard',
                    component: () => import( /* webpackChunkName: "dashboard" */ '../views/Dashboard.vue'),
                    meta: {
                        title: '系统首页',
                        requireAuth: true,
                        roles: [0, 1, 2]
                    },
                },
                {
                    path: '/photograph',
                    component: () => import( /* webpackChunkName: "photograph" */ '../views/Photograph.vue'),
                    meta: {
                        title: '即时拍照',
                        requireAuth: true
                    }

                },

                {
                    path: '/students',
                    component: () => import( /* webpackChunkName: "students" */ '../views/UsersManager/StuInfo.vue'),
                    meta: {
                        title: '学生信息管理',
                        requireAuth: true
                    }
                },
                {
                    path: '/teachers',
                    component: () => import( /* webpackChunkName: "teachers" */ '../views/UsersManager/TeachersInfo.vue'),
                    meta: {
                        title: '教师信息管理',
                        requireAuth: true
                    }
                },
                {
                    path: '/personInfo',
                    component: () => import( /* webpackChunkName: "personInfo" */ '../views/UsersManager/PersonInfo.vue'),
                    meta: {
                        title: '个人信息',
                        requireAuth: true
                    }
                },
                {
                    path: '/tabs',
                    component: () => import( /* webpackChunkName: "tabs" */ '../views/Tabs.vue'),
                    meta: {
                        title: '消息中心',
                        requireAuth: true
                    }
                },

            
                {
                    // 图片上传组件
                    path: '/uploadFace',
                    component: () => import( /* webpackChunkName: "uploadFace" */ '../views/FaceManager/UploadFace.vue'),
                    meta: {
                        title: '添加人脸',
                        requireAuth: true
                    }
                },
                {
                    // 图片上传更新组件
                    path: '/updateFace',
                    component: () => import( /* webpackChunkName: "updateFace" */ '../views/FaceManager/UpdateFace.vue'),
                    meta: {
                        title: '更新人脸',
                        requireAuth: true
                    }
                },
                {
                    // 图片上传更新组件-学生
                    path: '/studentsFaces',
                    component: () => import( /* webpackChunkName: "studentsFaces" */ '../views/FaceManager/StudentsFaces.vue'),
                    meta: {
                        title: '学生人脸管理',
                        requireAuth: true
                    }
                },
                {
                    // 图片上传更新组件-教师
                    path: '/teachersFaces',
                    component: () => import( /* webpackChunkName: "teachersFaces" */ '../views/FaceManager/TeachersFaces.vue'),
                    meta: {
                        title: '教师人脸管理',
                        requireAuth: true
                    }
                },

                {
                    path: '/changePwd',
                    component: () => import( /* webpackChunkName: "changePwd" */ '../views/AccountSettings/ChangePwd.vue'),
                    meta: {
                        title: '修改账户密码',
                        requireAuth: true
                    }
                },
                {
                    path: '/changePwdN',
                    component: () => import( /* webpackChunkName: "changePwdN" */ '../views/AccountSettings/ChangePwdN.vue'),
                    meta: {
                        title: '修改密保问题',
                        requireAuth: true
                    }
                },
                {
                    path: '/accountStatus',
                    component: () => import( /* webpackChunkName: "accountStatus" */ '../views/AccountSettings/AccountStatus.vue'),
                    meta: {
                        title: '账户冻结',
                        requireAuth: true
                    }
                },
                {
                    path: '/resetPwd',
                    component: () => import( /* webpackChunkName: "resetPwd" */ '../views/AccountSettings/ResetPwd.vue'),
                    meta: {
                        title: '重置密码'
                        ,
                        requireAuth: true
                    }
                },

                {
                    path: '/courses',
                    component: () => import( /* webpackChunkName: "courses" */ '../views/ClassTable/Courses.vue'),
                    meta: {
                        title: '课程表',
                        requireAuth: true
                    }
                },
                {
                    path: '/addcourse',
                    component: () => import( /* webpackChunkName: "addcourse" */ '../views/ClassTable/AddCourse.vue'),
                    meta: {
                        title: '添加课程',
                        requireAuth: true
                    }
                },
                {
                    path: '/arrangeCourse',
                    component: () => import( /* webpackChunkName: "arrangeCourse" */ '../views/ClassTable/ArrangeCourse.vue'),
                    meta: {
                        title: '排课',
                        requireAuth: true
                    }
                },
                {
                    path: '/studenttable',
                    component: () => import( /* webpackChunkName: "studenttable" */ '../views/ClassTable/StudentTable.vue'),
                    meta: {
                        title: '选修情况',
                        requireAuth: true
                    }
                },
                {
                    path: '/signin',
                    component: () => import( /* webpackChunkName: "signin" */ '../views/SignIn/SignIn.vue'),
                    meta: {
                        title: '考勤',
                        requireAuth: true
                    }
                },
                {
                    path: '/attendenceRecords',
                    component: () => import( /* webpackChunkName: "attendenceRecords" */ '../views/SignIn/AttendenceRecords.vue'),
                    meta: {
                        title: '考勤记录',
                        requireAuth: true
                    }
                },
                {
                    path: '/attendenceCourse',
                    component: () => import( /* webpackChunkName: "attendenceCourse" */ '../views/SignIn/AttendenceCourse.vue'),
                    meta: {
                        title: '考勤课程',
                        requireAuth: true
                    }
                },
                {
                    path: '/attendenceQuery',
                    component: () => import( /* webpackChunkName: "attendenceQuery" */ '../views/SignIn/AttendenceQuery.vue'),
                    meta: {
                        title: '出勤率',
                        requireAuth: true
                    }
                },
                { 
                    path: '/stuAttendenceRecords',
                    component: () => import( /* webpackChunkName: "stuAttendenceRecords" */ '../views/SignIn/StuAttendenceRecords.vue'),
                    meta: {
                        title: '考勤记录',
                        requireAuth: true
                    } 
                },
                { 
                    path: '/teachAttendenceRecords',
                    component: () => import( /* webpackChunkName: "teachAttendenceRecords" */ '../views/SignIn/TeachAttendenceRecords.vue'),
                    meta: {
                        title: '考勤记录',
                        requireAuth: true
                    } 
                },
                {
                    path: '/attendenceInfo',
                    component: () => import( /* webpackChunkName: "attendenceInfo" */ '../views/SignIn/AttendenceInfo.vue'),
                    meta: {
                        title: '课程出勤率',
                        requireAuth: true
                    }
                },
                {
                    path: '/recentAttendence',
                    component: () => import( /* webpackChunkName: "RecentAttendence" */ '../views/SignIn/RecentAttendence.vue'),
                    meta: {
                        title: '课程签到情况',
                        requireAuth: true
                    }
                },
                { 
                    path: '/roseJude',
                    component: () => import( /* webpackChunkName: "roseJude" */ '../views/SignIn/RoseJude.vue'),
                    meta: {
                        title: '角色判断',
                        requireAuth: true
                    } 
                },
                {
                    path: '/webSocket',
                    component: () => import( /* webpackChunkName: "webSocket" */ '../views/WebSocket/WebSocket.vue'),
                    meta: {
                        title: 'WebSocket',
                        requireAuth: true
                    }
                },

                {
                    path: '/404',
                    component: () => import( /* webpackChunkName: "404" */ '../views/404.vue'),
                    meta: {
                        title: '404',
                    }
                },
                {
                    path: '/403',
                    component: () => import( /* webpackChunkName: "403" */ '../views/403.vue'),
                    meta: {
                        title: '403'
                    }
                },

            ]
        },
        {
            path: '/login',
            component: () => import( /* webpackChunkName: "login" */ '../views/Login.vue'),
            meta: {
                title: '登录'
            }
        },
        {
            path: '*',
            redirect: '/404'
        }
    ]
});